#ifndef cas_H
#define cas_H

#include <opencv2/objdetect.hpp>
#include <opencv2/dnn/dnn.hpp>

#include "detector.h"

class cascadeDetection : public detector
{ Q_OBJECT
public:
    cascadeDetection(QObject *parent = nullptr);

    void setFrame(cv::Mat frame);
    void detect();
    void recieveImage(const cv::Mat image) override;

private:
    cv::CascadeClassifier fullBodyClassifier;
    cv::CascadeClassifier lowerBodyClassifier;
    cv::CascadeClassifier upperBodyClassifier;
    std::vector<cv::Rect> found;
    std::vector<int> levels;
    std::vector<double> weights;

    void sendQImage();
};



#endif
