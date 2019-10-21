#include "detector.h"

detector::detector(QObject *parent)
    : QObject(parent)
{
}

void detector::recieveImage(cv::Mat img)
{
}

void detector::sendQImage()
{
    if (this->fullsizeFrame.channels() == 3){
        cv::cvtColor(this->fullsizeFrame, this->fullsizeFrame, cv::COLOR_BGR2RGB);
        QFrame = QImage((const unsigned char*)(this->fullsizeFrame.data), this->fullsizeFrame.cols, this->fullsizeFrame.rows, QImage::Format_RGB888);
    }
    else
    {
        QFrame = QImage((const unsigned char*)(this->fullsizeFrame.data), this->fullsizeFrame.cols, this->fullsizeFrame.rows, QImage::Format_Indexed8);
    }
    emit this->processedImage(QFrame);
}

