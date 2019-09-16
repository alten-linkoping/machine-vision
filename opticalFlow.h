// Optical flow tracking
// opticalFlow.h

#ifndef opticalFlow_H
#define opticalFlow_H

#include <opencv2/opencv.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/core/ocl.hpp>
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include <node.h>

class opticalFlow
{
public:
	opticalFlow(){};
	~opticalFlow() = default;
	
	void calculateFlow();
	std::vector<std::vector<int> > getBoxes();
	void setFrame(cv::Mat frame);



private:
	cv::Mat frame; 						// The current frame
	cv::Mat flow, cflow, gray, prevgray, img_bgr, img_hsv, gray_bgr;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy; 
	std::vector<std::vector<int> > boxes;
 

	void detectEdges();
	void drawHsv();
	void drawOptFlowMap(double scale, int step, const cv::Scalar& color);

};



#endif