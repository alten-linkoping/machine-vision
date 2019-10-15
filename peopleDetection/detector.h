#ifndef DETECTOR_H
#define DETECTOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"

#include <QImage>

class detector : public QObject
{ Q_OBJECT

public:
    detector(QObject *parent = nullptr);
    ~detector() = default;

    void virtual recieveImage(const cv::Mat image);
    cv::Mat frame;
    QImage QFrame;


signals:
    void processedImage(const QImage &image);

private:

};

#endif // DETECTOR_H
