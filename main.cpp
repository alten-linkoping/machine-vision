// main.cpp
//#include "motionDetection.h"
#include "opticalFlow.h"
#include <iostream>
#include <string>
#include <napi.h>

std::string hello()
{
	// code 
	std::vector<cv::String> fn;
	cv::glob("MOT17-09-FRCNN/img1/00000*.jpg", fn, false);

	opticalFlow OF;
	std::vector<std::vector<int> > tempBoxCoords;
	std::string imageBoxCoordinates;
	imageBoxCoordinates.append("{");

	// Load and calculate on the first frame
	OF.setFrame(cv::imread(fn[0]));
	OF.calculateFlow();


	for (size_t i=1; i<fn.size(); i++)
	{
		OF.setFrame(cv::imread(fn[i]));
		OF.calculateFlow();

		tempBoxCoords = OF.getBoxes();
		std::string tempName = fn[i];
	
		imageBoxCoordinates.append("\"" + tempName.erase(0,20) + "\"");
		imageBoxCoordinates.append(":{");
    	
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



Napi::String HelloWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, hello());
  
  return returnValue;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set(
"hello", Napi::Function::New(env, HelloWrapped)
  );
 
  return exports;
}



int main(int argc, char const *argv[])
{
	// code 
	std::vector<cv::String> fn;
	cv::glob("MOT17-09-FRCNN/img1/00000*.jpg", fn, false);

	opticalFlow OF;
	std::vector<std::vector<int> > tempBoxCoords;
	std::string imageBoxCoordinates;
	imageBoxCoordinates.append("{");

	// Load and calculate on the first frame
	OF.setFrame(cv::imread(fn[0]));
	OF.calculateFlow();


	for (size_t i=1; i<fn.size(); i++)
	{
		OF.setFrame(cv::imread(fn[i]));
		OF.calculateFlow();

		tempBoxCoords = OF.getBoxes();
		std::string tempName = fn[i];
	
		imageBoxCoordinates.append("\"" + tempName.erase(0,20) + "\"");
		imageBoxCoordinates.append(":{");
    	
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


		if (i == fn.size()-1)
		{
			imageBoxCoordinates.append("}");
		}
		else
		{
			imageBoxCoordinates.append(",");
		}

		
	}

	std::cout << imageBoxCoordinates << std::endl;
	
    return 0;
}

NODE_API_MODULE(opticalFlow_addon, Init)


