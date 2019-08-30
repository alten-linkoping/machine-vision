// main.cpp
#include "motionDetection.h"
#include <iostream>
#include <string>


int main(int argc, char const *argv[])
{
	/* code */
	std::vector<cv::String> fn;
	cv::glob("MOT17-09-FRCNN/img1/*.jpg", fn, false);

	std::vector<cv::Mat> images;
	size_t count = fn.size(); //number of jpg files in images folder
	for (size_t i=0; i<count; i++)
    	images.push_back(cv::imread(fn[i]));

	motionDetection *MD = new motionDetection(images);
	MD->setupTracker("MEDIANFLOW");
	std::cout << "It works" << std::endl;
	std::cout << "Images read: " << MD->getImages().size() << std::endl;

	namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
	for (int i = 0; i < MD->getImages().size(); ++i)
	{
		    imshow( "Display window", MD->getImages()[i]);                   // Show our image inside it.

    		cv::waitKey(25); 
	}
                                         // Wait for a keystroke in the window
    return 0;
}