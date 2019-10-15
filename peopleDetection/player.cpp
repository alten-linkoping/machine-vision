#include "player.h"

Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    cap.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::setDetector(QString detectorName)
{
    if (detectorName == "Motion")
    {
        detector = new opticalFlow();
    }
    else if (detectorName == "HOG")
    {
        detector = new HOGDetection();
    }
    else if (detectorName == "Cascade")
    {
        detector = new cascadeDetection();
    }
}

bool Player::loadVideo(std::string filename)
{
    this->cap.open(filename);

    if (this->cap.isOpened())
    {
        this->frameRate = (int) this->cap.get(cv::CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void Player::Play()
{
    if (!isRunning())
    {
        if(this->isStopped())
        {
            this->stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
    int delay = (100/this->frameRate);

    while(!this->stop)
    {
            if (!this->cap.read(frame))
            {
                this->stop = true;
            }

            else if (this->frame.channels() == 3){
                this->detector->recieveImage(this->frame);

                //connect ad recieve image with detection
                QObject::connect(this->detector, SIGNAL(processedImage(QImage)),
                                 this, SLOT(recieveProcessedImage(QImage)));
                //QFrame = detectionImage;
            }

        emit this->processedImage(this->detectionImage);

        this->msleep(delay);
    }
}

void Player::Stop()
{
    stop = true;
}

void Player::msleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::isStopped() const
{
    return this->stop;
}

void Player::recieveProcessedImage(QImage img)
{
    if (!img.isNull())
    {
        this->detectionImage = img;
    }
}
