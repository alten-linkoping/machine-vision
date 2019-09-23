// main.cpp
//#include "motionDetection.h"
#include "opticalFlow.h"
#include "HOGDetection.h"
#include <iostream>
#include <string>
#include <napi.h>
//std::vector<std::string> > dataSets = ["MOT17-09-FRCNN","MOT17-08-DPM"];


#include <boost/algorithm/string.hpp> 




std::vector<std::string> dataSets = {"MOT17-09-FRCNN", "MOT17-08-FRCNN", "MOT17-04-SDP"};

std::string hello(int dataset)
{
	// code 
	std::vector<cv::String> fn;

	cv::glob("public/"+ dataSets[dataset-1]+"/img1/00000*.jpg", fn, false);

	//opticalFlow OF;
	HOGDetection HOG;
	std::vector<std::vector<int> > tempBoxCoords;
	std::string imageBoxCoordinates;
	imageBoxCoordinates.append("{");

	// Load and calculate on the first frame
	cv::Mat resizedImage;
	cv::resize(cv::imread(fn[0], CV_LOAD_IMAGE_COLOR), resizedImage, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_NEAREST);
	//OF.setFrame(resizedImage);
	//OF.calculateFlow();


	for (size_t i=0; i<fn.size(); i++)
	{
		cv::resize(cv::imread(fn[i], CV_LOAD_IMAGE_COLOR), resizedImage, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_NEAREST);
		//OF.setFrame(cv::imread(fn[i]));
		//OF.setFrame(resizedImage);
		//OF.calculateFlow();
		HOG.setFrame(resizedImage);
		HOG.detect();

		//tempBoxCoords = OF.getBoxes();
		tempBoxCoords = HOG.getBoxes();
		std::string tempName = fn[i];
	
		imageBoxCoordinates.append("\"" + tempName.erase(0,27) + "\"");
		imageBoxCoordinates.append(":{");
    	
    	if(!tempBoxCoords.empty())
    	{
	    	for (int j = 0; j < tempBoxCoords.size(); j++)
	   		{
	   			
		     	imageBoxCoordinates.append("\"");
		     	imageBoxCoordinates.append("Box" + std::to_string(j+1));
		     	imageBoxCoordinates.append("\"");
		     	imageBoxCoordinates.append(":");
		     	imageBoxCoordinates.append("\"");
		     	std::string coord = "";
		     	coord = std::to_string(tempBoxCoords[j][0]) + "," + std::to_string(tempBoxCoords[j][1]) + "," + std::to_string(tempBoxCoords[j][2]) + "," + std::to_string(tempBoxCoords[j][3]);
		     	imageBoxCoordinates.append(coord);
		     	imageBoxCoordinates.append("\"");

		     	if (j != tempBoxCoords.size()-1)
		     	{
		      	 	imageBoxCoordinates.append(",");
		     	}
		     	else
		     	{
		     		imageBoxCoordinates.append("}");
		     	}
	   		}
   		}

		if (i == fn.size()-1)
		{
			imageBoxCoordinates.append("}");
		}
		else
		{
			imageBoxCoordinates.append(",");
		}
	}
	    return imageBoxCoordinates;
}




Napi::String AddWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    } 

    Napi::Number first = info[0].As<Napi::Number>();
    

    //int returnValue = add(first.Int32Value());
	Napi::String returnValue = Napi::String::New(env, hello(first.Int32Value()));
    
    return returnValue;
}


Napi::Object Init(Napi::Env env, Napi::Object exports) 
{

  exports.Set("add", Napi::Function::New(env, AddWrapped));
 
  return exports;
}


NODE_API_MODULE(opticalFlow_addon, Init)


