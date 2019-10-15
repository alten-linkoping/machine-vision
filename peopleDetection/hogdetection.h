#ifndef HOG_H
#define HOG_H

#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/dnn/dnn.hpp>

#include "detector.h"

class HOGDetection : public detector
{ Q_OBJECT
public:
    HOGDetection(QObject *parent = nullptr);

    void setFrame(cv::Mat frame);
    void detect();
    void recieveImage(const cv::Mat image) override;

private:
    cv::HOGDescriptor hog_d = cv::HOGDescriptor(cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
    cv::HOGDescriptor hog = cv::HOGDescriptor(cv::Size(64,128), cv::Size(16,16), cv::Size(8,8), cv::Size(8,8), 9);
    std::vector<cv::Rect> found;
    std::vector< double > foundScores;
    void adjustRect(cv::Rect & r) const;

    void sendQImage();
};

#endif
