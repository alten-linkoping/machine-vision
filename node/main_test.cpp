#include "opticalFlow.h"
#include "HOGDetection.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
	// code 
	std::vector<cv::String> fn;
	cv::glob("MOT17-09-FRCNN/img1/*.jpg", fn, false);

	HOGDetection HOG;
	cv::Mat resizedImage;

	for (int i = 0; i < fn.size(); ++i)
	{
		cv::resize(cv::imread(fn[i], CV_LOAD_IMAGE_COLOR), resizedImage, cv::Size(), 0.25, 0.25, cv::INTER_NEAREST);
	
		HOG.setFrame(resizedImage);
		HOG.detect();
	}
	
    return 0;
}