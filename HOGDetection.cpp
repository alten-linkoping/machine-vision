#include "HOGDetection.h"

HOGDetection::HOGDetection()
{
	this->hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

void HOGDetection::setFrame(cv::Mat frame)
{
	this->frame = frame;
	this->found.clear();
	this->bboxes.clear();
}

std::vector<std::vector<int> > HOGDetection::getBoxes()
{
	return this->bboxes;
}

void HOGDetection::detect()
{
	cv::namedWindow("HOG", cv::WINDOW_AUTOSIZE);

	this->hog.detectMultiScale(this->frame, this->found, 0.0, cv::Size(8,8), cv::Size(), 1.05, 2, false);

if(!found.empty()){
	for (int i = 0; i < this->found.size(); ++i)
	{
		adjustRect(this->found[i]);
		rectangle(this->frame,
						this->found[i].tl(), this->found[i].br(),
						cv::Scalar(0, 255, 0), 2);
		this->bboxes.push_back(std::vector<int> {this->found[i].x/2, this->found[i].y/2, this->found[i].height/2, this->found[i].width/2});
	}
}

	imshow("HOG", this->frame);
	cv::waitKey(5);
}

void HOGDetection::adjustRect(cv::Rect & r) const
    {
        // The HOG detector returns slightly larger rectangles than the real objects,
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
    }