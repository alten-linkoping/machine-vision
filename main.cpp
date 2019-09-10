// main.cpp
//#include "motionDetection.h"
#include "opticalFlow.h"
#include <iostream>
#include <string>

void init(v8::Local<v8::Object> exports, auto Method)
	{
  		NODE_SET_METHOD(exports, "opticalFlow", Method);
	}

int main(int argc, char const *argv[])
{
	/* code */
	std::vector<cv::String> fn;
	cv::glob("MOT17-09-FRCNN/img1/*.jpg", fn, false);

	std::vector<cv::Mat> images;
	size_t count = fn.size(); //number of jpg files in images folder
	for (size_t i=0; i<count; i++)
    	images.push_back(cv::imread(fn[i]));

	/*
	motionDetection *MD = new motionDetection(images);
	MD->LKTracker();
	MD->setupTracker("MEDIANFLOW");
	std::cout << "It works" << std::endl;
	std::cout << "Images read: " << MD->getImages().size() << std::endl;
	
	namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
	for (int i = 0; i < MD->getImages().size(); ++i)
	{
		    imshow( "Display window", MD->getImages()[i]);                   // Show our image inside it.

    		cv::waitKey(25); 
	}
          */                                // Wait for a keystroke in the window

    opticalFlow *OF = new opticalFlow(images);
    OF->calculateFlow();

	NODE_MODULE(opticalFlow_addon, init(OF->sendJson()));

    return 0;
   
}