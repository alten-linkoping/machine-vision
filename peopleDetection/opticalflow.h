#ifndef opticalFlow_H
#define opticalFlow_H

#include "detector.h"

class opticalFlow : public detector
{ Q_OBJECT
public:
    opticalFlow(QObject *parent = nullptr);
    void calculateFlow();
    void setFrame(cv::Mat frame);
    void recieveImage(const cv::Mat image) override;

signals:
    void processedImage(const QImage &image);

private:					// The current frame
    cv::Mat flow, cflow, gray, prevgray, img_bgr, img_hsv, gray_bgr;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    void detectEdges();
    void drawHsv();
    void drawOptFlowMap(double scale, int step, const cv::Scalar& color);
};


#endif
