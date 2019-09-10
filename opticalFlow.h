// Optical flow tracking
// opticalFlow.h

#ifndef opticalFlow_H
#define opticalFlow_H

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <node.h>
#include <string>

class opticalFlow
{
public:
	opticalFlow(std::vector<cv::Mat> loadedImages, std::vector<std::string> loadedImageNames);
	~opticalFlow() = default;
	
	void calculateFlow();
	void sendJson(const v8::FunctionCallbackInfo<v8::Value> &args);


private:
	std::vector<cv::Mat> images;		// All of the images i the sequence 
	std::vector<std::string> imageNames;
	int currentFrame = 0;						// The current frame
	cv::Mat flow, cflow, gray, prevgray, img_bgr, img_hsv, gray_bgr;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy; 
	std::vector<std::vector<int> > boxes;
	v8::Local<v8::Object> obj;
	v8::Isolate *isolate;

	void detectEdges();
	void drawHsv();
	void drawOptFlowMap(double scale, int step, const cv::Scalar& color);
	void createJsonObj(const v8::FunctionCallbackInfo<v8::Value> &args);
	void addToJson();
	

};



#endif