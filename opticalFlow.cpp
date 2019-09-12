// opticalFlow.cpp

#include "opticalFlow.h"

void opticalFlow::setFrame(cv::Mat frame)
{
	this->frame = frame;
}

std::vector<std::vector<int> > opticalFlow::getBoxes()
{
	return this->boxes;
}

void opticalFlow::detectEdges()
{
	/// Detect edges using Threshold
			cv::Mat img_thresh = cv::Mat::zeros(this->frame.rows, this->frame.cols, CV_8UC1);
			cv::threshold(this->gray_bgr, img_thresh, 245, 255, cv::THRESH_BINARY_INV);
			cv::dilate(img_thresh, img_thresh, 0, cv::Point(-1, -1), 30);
			cv::erode(img_thresh, img_thresh, 0, cv::Point(-1, -1), 30);
			cv::dilate(img_thresh, img_thresh, 0, cv::Point(-1, -1), 30);
			//imshow("tresh",img_thresh);
			cv::findContours(img_thresh, this->contours, this->hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (auto i = 0; i < this->contours.size(); i++)
			{
				std::vector<std::vector<cv::Point> > contours_poly(this->contours.size());
				cv::approxPolyDP(cv::Mat(this->contours[i]), contours_poly[i], 3, true);
				cv::Rect box = cv::boundingRect(cv::Mat(contours_poly[i]));
				if (box.width > 50 && box.height > 50 && box.width < 800 && box.height < 900) {
					rectangle(this->frame,
						box.tl(), box.br(),
						cv::Scalar(0, 255, 0), 4);
						this->boxes.push_back(std::vector<int> {box.x, box.y, box.height, box.width});
				}
			
			}
	

			/// Show in a window
			//cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
			//imshow("Contours", this->frame);
}

void opticalFlow::calculateFlow()
{
	this->boxes.clear();
	//cv::namedWindow("flow", cv::WINDOW_AUTOSIZE);

		cv::cvtColor(this->frame, this->gray, cv::COLOR_BGR2GRAY);


		if (!prevgray.empty())
		{
			// Calculate the optical flow using the Farneback method using the gray scale image of the current and previous frame.
			cv::calcOpticalFlowFarneback(this->prevgray, this->gray, this->flow, 0.5, 10, 32, 3, 7, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
			// void calcOpticalFlowFarneback(InputArray prev, InputArray next, InputOutputArray flow, double pyr_scale, int levels, int winsize, int iterations, int poly_n, double poly_sigma, int flags)
			
			// 
			cv::cvtColor(this->prevgray, this->cflow, cv::COLOR_GRAY2BGR);
			drawOptFlowMap(0.5, 16, CV_RGB(0, 255, 0));
			//imshow("flow", this->cflow);
			this->drawHsv();
			this->gray_bgr = cv::Mat::zeros(this->frame.rows, this->frame.cols, CV_8UC1);
			cv::cvtColor(this->img_bgr, this->gray_bgr, CV_BGR2GRAY);
			cv::normalize(this->gray_bgr, this->gray_bgr, 0, 255, cv::NORM_MINMAX, CV_8UC1);
			cv::blur(this->gray_bgr, this->gray_bgr, cv::Size(5, 5));
			//imshow("gray", this->gray_bgr);

			this->detectEdges();

		}
		//cv::waitKey(5); 
		std::swap(this->prevgray, this->gray);
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
		1.5 / mag_max // scaling factor
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


