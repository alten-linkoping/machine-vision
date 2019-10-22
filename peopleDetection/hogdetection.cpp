#include "hogdetection.h"

HOGDetection::HOGDetection(QObject *parent)
    : detector(parent)
{
    this->hog_d.setSVMDetector(cv::HOGDescriptor::getDaimlerPeopleDetector());
    this->hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

void HOGDetection::setFrame(cv::Mat img)
{
    cv::cvtColor(img, this->frame, cv::COLOR_BGR2GRAY);
    this->found.clear();
    this->foundScores.clear();
}

void HOGDetection::detect()
{
    std::vector<cv::Rect> tempFound;
    std::vector<double> tempFoundScore;

    this->hog_d.detectMultiScale(this->frame, this->found, this->foundScores, 0.0, cv::Size(8,8), cv::Size(4,4), 1.05, 2, true);
    //this->hog.detectMultiScale(this->frame, tempFound, tempFoundScore, 0.0, cv::Size(8,8), cv::Size(12,12), 1.08, 2, false);

    this->found.insert(this->found.end(), tempFound.begin(), tempFound.end());
    this->foundScores.insert(this->foundScores.end(), tempFoundScore.begin(), tempFoundScore.end());

    std::vector<int> indices;
    std::vector<float> confidences;

    for (int i = 0; i < this->foundScores.size(); ++i)
    {
        confidences.push_back((float) this->foundScores[i]);
    }

    //Remove boxes that overlaps to much. Non Max Suppresion.
    cv::dnn::NMSBoxes(this->found, confidences, 0.2, 0.3, indices);


    if(!found.empty()){
        for (int i = 0; i < indices.size(); ++i)
        {
            adjustRect(this->found[indices[i]]);
            rectangle(this->fullsizeFrame,
                            this->found[indices[i]].tl()*2, this->found[indices[i]].br()*2,
                            cv::Scalar(0, 255, 0), 2);
            }
    }
    this->sendQImage();
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

void HOGDetection::recieveImage(cv::Mat img)
{
    cv::resize(img, this->frame, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_NEAREST);
    this->setFrame(this->frame);
    this->fullsizeFrame = img;

    this->detect();
}

