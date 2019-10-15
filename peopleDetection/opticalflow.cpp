#include "opticalflow.h"

opticalFlow::opticalFlow(QObject *parent)
    : detector(parent)
{
}

void opticalFlow::setFrame(cv::Mat frame)
{
    this->frame = frame;
}

void opticalFlow::detectEdges()
{
    /// Detect edges using Threshold
            cv::Mat img_thresh = cv::Mat::zeros(this->frame.rows, this->frame.cols, CV_8UC1);
            cv::threshold(this->gray_bgr, img_thresh, 242, 255, cv::THRESH_BINARY_INV);

            cv::dilate(img_thresh, img_thresh, 0, cv::Point(-1, -1), 10);
            cv::erode(img_thresh, img_thresh, 0, cv::Point(-1, -1), 8);
            //cv::dilate(img_thresh, img_thresh, 0, cv::Point(-1, -1), 10);

            cv::findContours(img_thresh, this->contours, this->hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
            for (auto i = 0; i < this->contours.size(); i++)
            {
                std::vector<std::vector<cv::Point> > contours_poly(this->contours.size());
                cv::approxPolyDP(cv::Mat(this->contours[i]), contours_poly[i], 3, true);
                cv::Rect box = cv::boundingRect(cv::Mat(contours_poly[i]));
                if (box.width > 50 && box.height > 50) {
                    rectangle(this->frame,
                        box.tl(), box.br(),
                        cv::Scalar(0, 255, 0), 2);
                      }
            }
}

void opticalFlow::calculateFlow()
{
    cv::cvtColor(this->frame, this->gray, cv::COLOR_BGR2GRAY);

        if (!prevgray.empty())
        {
            // Calculate the optical flow using the Farneback method using the gray scale image of the current and previous frame.
            cv::calcOpticalFlowFarneback(this->prevgray, this->gray, this->flow, 0.5, 5, 25, 3, 7, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
            // void calcOpticalFlowFarneback(InputArray prev, InputArray next, InputOutputArray flow, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)

            cv::cvtColor(this->prevgray, this->cflow, cv::COLOR_GRAY2BGR);
            drawOptFlowMap(0.5, 12, CV_RGB(0, 255, 0));
            this->drawHsv();
            this->gray_bgr = cv::Mat::zeros(this->frame.rows, this->frame.cols, CV_8UC1);
            cv::cvtColor(this->img_bgr, this->gray_bgr, cv::COLOR_BGR2GRAY);
            cv::normalize(this->gray_bgr, this->gray_bgr, 0, 255, cv::NORM_MINMAX, CV_8UC1);
            cv::GaussianBlur(this->gray_bgr, this->gray_bgr, cv::Size(15,15), 0, 0);

            this->detectEdges();
        }
    std::swap(this->prevgray, this->gray);

    this->sendQImage();

}

void opticalFlow::drawHsv() {
    //extract x and y channels
    cv::Mat xy[2]; //X,Y
    cv::split(this->flow, xy);

    //calculate angle and magnitude
    cv::Mat magnitude, angle, hsv;
    cv::cartToPolar(xy[0], xy[1], magnitude, angle, true);

    //translate magnitude to range [0;1]
    double mag_max;
    cv::minMaxLoc(magnitude, 0, &mag_max);
    magnitude.convertTo(
        magnitude,    // output matrix
        -1,           // type of the ouput matrix, if negative same type as input matrix
        5 / mag_max // scaling factor
    );

    const double PI = std::atan(1.0)*4;

    //build hsv image
    cv::Mat _hsv[3];
    _hsv[0] = angle*180/PI/2;
    _hsv[1] = cv::Mat::ones(angle.size(), CV_32F)*255;
    _hsv[2] = cv::min(magnitude*45, 255);
    //cv::normalize(magnitude, _hsv[1], 0, 255, cv::NORM_MINMAX);

    cv::merge(_hsv, 3, hsv);
    //convert to BGR and show
    cv::cvtColor(hsv, this->img_bgr, cv::COLOR_HSV2BGR);
}


void opticalFlow::drawOptFlowMap(double scale, int step, const cv::Scalar& color)
{
    for (int y = 0; y < this->cflow.rows; y += step)
        for (int x = 0; x < this->cflow.cols; x += step)
        {
            const cv::Point2f& fxy = this->flow.at<cv::Point2f>(y, x) * scale;
            cv::line(this->cflow, cv::Point(x, y), cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)),
                color);
            cv::circle(this->cflow, cv::Point(x, y), 2, color, -1);
        }
}

void opticalFlow::recieveImage(cv::Mat img)
{
    cv::resize(img, this->frame, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_NEAREST);

    this->calculateFlow();
}

void opticalFlow::sendQImage()
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

