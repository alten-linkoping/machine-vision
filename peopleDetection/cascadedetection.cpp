#include "cascadedetection.h"

cascadeDetection::cascadeDetection(QObject *parent)
    : detector(parent)
{
    this->fullBodyClassifier.load("haarcascade_fullbody.xml");
    this->upperBodyClassifier.load("haarcascade_upperbody.xml");
    this->lowerBodyClassifier.load("haarcascade_lowerbody.xml");
}

void cascadeDetection::setFrame(cv::Mat img)
{
    //cv::cvtColor(frame, this->frame, CV_BGR2GRAY);
    this->frame = img;
    this->found.clear();
    this->levels.clear();
    this->weights.clear();
}

void cascadeDetection::detect()
{
    std::vector<cv::Rect> tempFound;
    std::vector<double> tempWeights;

    this->fullBodyClassifier.detectMultiScale(this->frame, this->found, this->levels, this->weights, 1.1, 3, 0, cv::Size(20,10), cv::Size(800,500), true);

    std::vector<int> indices;
    std::vector<float> confidences;

    for (auto i = 0; i < this->weights.size(); ++i)
    {
        confidences.push_back((float) this->weights[i]);
    }

    //Remove boxes that overlaps to much. Non Max Suppresion.
    cv::dnn::NMSBoxes(this->found, confidences, 0.2, 0.9, indices);


    if(!found.empty()){
        for (auto i = 0; i < indices.size(); ++i)
        {
            rectangle(this->frame,
                        this->found[indices[i]].tl(), this->found[indices[i]].br(),
                        cv::Scalar(0, 255, 0), 2);
        }
    }

    this->sendQImage();
}

void cascadeDetection::recieveImage(cv::Mat img)
{
    cv::resize(img, this->frame, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_NEAREST);
    this->setFrame(this->frame);

    this->detect();
}

void cascadeDetection::sendQImage()
{
    if (this->frame.channels() == 3){
        cv::cvtColor(this->frame, this->frame, cv::COLOR_BGR2RGB);
        QFrame = QImage((const unsigned char*)(this->frame.data), this->frame.cols, this->frame.rows, QImage::Format_RGB888);
    }
    else
    {
        QFrame = QImage((const unsigned char*)(this->frame.data), this->frame.cols, this->frame.rows, QImage::Format_Indexed8);
    }
    emit this->processedImage(QFrame);
}
