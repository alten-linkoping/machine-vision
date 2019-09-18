#ifndef HOG_H
#define HOG_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>



class HOGDetection
{
public:
	HOGDetection();
	~HOGDetection() = default;
	
	std::vector<std::vector<int> > getBoxes();
	void setFrame(cv::Mat frame);
	void detect();

private:
	cv::Mat frame; 						// The current frame
	cv::HOGDescriptor hog = cv::HOGDescriptor(cv::Size(48, 96), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
	//cv::HOGDescriptor hog;
	std::vector<cv::Rect> found;
	std::vector<std::vector<int> > bboxes;
	void adjustRect(cv::Rect & r) const;

};



#endif
