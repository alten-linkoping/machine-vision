// Optical flow tracking
// opticalFlow.h

#ifndef opticalFlow_H
#define opticalFlow_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class opticalFlow
{
public:
	opticalFlow(std::vector<cv::Mat> loadedImages);
	~opticalFlow() = default;
	void calculateFlow();
	void drawHsv();
	void drawOptFlowMap(double scale, int step, const cv::Scalar& color);

	

private:
	std::vector<cv::Mat> images;		// All of the images i the sequence 
	cv::Mat Frame;						// The current frame
	cv::Mat flow, cflow, frame, gray, prevgray, img_bgr, img_hsv;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy; 

};



#endif