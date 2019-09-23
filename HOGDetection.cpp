#include "HOGDetection.h"

HOGDetection::HOGDetection()
{
	this->hog.setSVMDetector(cv::HOGDescriptor::getDaimlerPeopleDetector());
}

void HOGDetection::setFrame(cv::Mat frame)
{
	this->frame = frame;
	this->found.clear();
	this->foundScores.clear();
	this->bboxes.clear();
}

std::vector<std::vector<int> > HOGDetection::getBoxes()
{
	return this->bboxes;
}

void HOGDetection::detect()
{
	cv::namedWindow("HOG", cv::WINDOW_AUTOSIZE);

	this->hog.detectMultiScale(this->frame, this->found, this->foundScores, 0.0, cv::Size(8,8), cv::Size(4,4), 1.05, 2, true);
	std::vector<int> indices;
	std::vector<float> confidences;

	for (int i = 0; i < this->foundScores.size(); ++i)
	{
		confidences.push_back((float) this->foundScores[i]);
	}

	//Remove boxes that overlaps to much. Non Max Suppresion.
	cv::dnn::NMSBoxes(this->found, confidences, 0.3, 0.15, indices);

if(!found.empty()){
	for (int i = 0; i < indices.size(); ++i)
	{
		adjustRect(this->found[indices[i]]);
		rectangle(this->frame,
						this->found[indices[i]].tl(), this->found[indices[i]].br(),
						cv::Scalar(0, 255, 0), 2);
		this->bboxes.push_back(std::vector<int> {this->found[indices[i]].x/2, this->found[indices[i]].y/2, this->found[indices[i]].height/2, this->found[indices[i]].width/2});
	}
}

	//imshow("HOG", this->frame);
	//cv::waitKey(5);
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