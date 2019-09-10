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
	std::vector<std::string> imageNames;
	size_t count = fn.size(); //number of jpg files in images folder
	for (size_t i=0; i<count; i++)
	{
    	images.push_back(cv::imread(fn[i]));
    	imageNames.push_back(std::string(fn.erase(fn.begin(), fn.end()-8)));
	}


    opticalFlow *OF = new opticalFlow(images);
    OF->calculateFlow();

	NODE_MODULE(opticalFlow_addon, init(OF->sendJson()));

    return 0;
   
}