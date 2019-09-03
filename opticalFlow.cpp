// opticalFlow.cpp

#include "opticalFlow.h"


opticalFlow::opticalFlow(std::vector<cv::Mat> loadedImages)
{
	this->images = loadedImages;
				
}

void opticalFlow::calculateFlow()
{
	cv::namedWindow("flow", cv::WINDOW_AUTOSIZE);

	for (int i = 0; i < this->images.size(); ++i)
	{
		this->frame = this->images[i];
		cv::cvtColor(this->frame, this->gray, cv::COLOR_BGR2GRAY);


		if (!prevgray.empty())
		{
			// Calculate the optical flow using the Farneback method using the gray scale image of the current and previous frame.
			cv::calcOpticalFlowFarneback(this->prevgray, this->gray, this->flow, 0.5, 5, 32, 3, 7, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
			// void calcOpticalFlowFarneback(InputArray prev, InputArray next, InputOutputArray flow, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)
			
			// 
			cv::cvtColor(this->prevgray, this->cflow, cv::COLOR_GRAY2BGR);
			drawOptFlowMap(0.5, 16, CV_RGB(0, 255, 0));
			imshow("flow", this->cflow);
			//drawHsv();
			//cv::Mat gray_bgr = cv::Mat::zeros(this->frame.rows, this->frame.cols, CV_8UC1);
			//cv::cvtColor(img_bgr, gray_bgr, CV_BGR2GRAY);
			//cv::normalize(gray_bgr, gray_bgr, 0, 255, cv::NORM_MINMAX, CV_8UC1);
			//cv::blur(gray_bgr, gray_bgr, cv::Size(3, 3));
			//imshow("gray", gray_bgr);


		}
		cv::waitKey(5); 
		std::swap(this->prevgray, this->gray);
	}
	
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
		1.0 / mag_max // scaling factor
	);


	//build hsv image
	cv::Mat _hsv[3];
	_hsv[0] = angle;
	_hsv[1] = magnitude;
	_hsv[2] = cv::Mat::ones(angle.size(), CV_32F);

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
