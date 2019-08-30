// motionDetection.cpp

#include "motionDetection.h"


motionDetection::motionDetection(std::vector<cv::Mat> loadedImages)
{
	this->images = loadedImages;
	this->frame = this->images[0];			//sets the first image in the video to the first frame
}


cv::Ptr<cv::Tracker> motionDetection::createTrackerByName(std::string trackerType) 
{

  if (trackerType ==  this->trackerTypes[0])
    this->tracker = cv::TrackerBoosting::create();
  else if (trackerType == this->trackerTypes[1])
    this->tracker = cv::TrackerMIL::create();
  else if (trackerType == this->trackerTypes[2])
    this->tracker = cv::TrackerKCF::create();
  else if (trackerType == this->trackerTypes[3])
    this->tracker = cv::TrackerTLD::create();
  else if (trackerType == this->trackerTypes[4])
    this->tracker = cv::TrackerMedianFlow::create();
  else if (trackerType == this->trackerTypes[5])
    this->tracker = cv::TrackerGOTURN::create();
  else if (trackerType == this->trackerTypes[6])
    this->tracker = cv::TrackerMOSSE::create();
  else if (trackerType == this->trackerTypes[7])
    this->tracker = cv::TrackerCSRT::create();

    
  return tracker;
}

void motionDetection::LKTracker()
{
	// Corner detection to initialize points to track

    cv::cvtColor(this->frame, this->nextGray, COLOR_BGR2GRAY);

    cv::Mat points = cv::Mat::zeros(this->nextGray.size(), cv::CV_32F);
    cv::cornerHarris(this->nextGray, points, blockSize, apertureSize, k);
}

void motionDetection::setupTracker(std::string const trackerType)
{
	bool showCrosshair = true;
	bool fromCenter = false;

	//cv::selectROIs("MultiTracker", this->frame, this->bboxes, showCrosshair, fromCenter); //Not what i wanted

	this->getRandomColors(this->colors, this->bboxes.size());

	for (int n = 0; n < this->bboxes.size(); ++n)
	{
		for (int i = 0; i < this->trackerTypes.size(); ++i)
		{
			if (trackerType == this->trackerTypes[i])
			{
				this->multiTracker->add(this->createTrackerByName(trackerType), this->frame, cv::Rect2d(this->bboxes[n]));
			}
		}
	}
}
	

// Fill the vector with random colors
void motionDetection::getRandomColors(std::vector<cv::Scalar>& colors, int numColors)
{
	cv::RNG rng(0);
	for(int i=0; i < numColors; i++)
		this->colors.push_back(cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255))); 
}

std::vector<cv::Mat> motionDetection::getImages()
{
	return this->images;
}