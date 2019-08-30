//motionDetection.h
/* 
A class for motion detection and tracking using optical flow to detect movement and a tracking algorithm of the users choice. 
*/
#ifndef motionDetection_H
#define motionDetection_H

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

class motionDetection
{
public:
	motionDetection(std::vector<cv::Mat> loadedImages);
	~motionDetection() = default;

	cv::Ptr<cv::Tracker> createTrackerByName(std::string trackerType); 
	void LKTracker();
	void setupTracker(std::string const trackerType);
	std::vector<cv::Mat> getImages();
	

private:
	void getRandomColors(std::vector<cv::Scalar>& colors, int numColors);
	std::vector<std::string> trackerTypes = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};
	cv::Ptr<cv::MultiTracker> multiTracker = cv::MultiTracker::create();
	cv::Ptr<cv::Tracker> tracker;
	std::vector<cv::Mat> images;
	std::vector<cv::Rect> bboxes;
	std::vector<cv::Scalar> colors; 
	cv::Mat outImage;                  // the output image in title window
    cv::Mat frame;                  // buffer of current frame from video
    cv::Mat priorGray;              // prior frame in grayscale
    cv::Mat nextGray;               // current frame in grayscale

    std::vector<cv::Point2f> priorPoints; // tracking points in priorGray
    std::vector<cv::Point2f> nextPoints;  // tracking points in nextGray
    std::vector<cv::Mat> priorPyramid;    // flow pyramid from priorGray
    std::vector<cv::Mat> nextPyramid;     // flow pyramid from nextGray

    // Parameter values for the Harris corner detection algortihm
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
};



#endif