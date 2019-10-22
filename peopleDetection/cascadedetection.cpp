#include "cascadedetection.h"

cascadeDetection::cascadeDetection(QObject *parent)
    : detector(parent)
{
    std::cout << "Classifier: " << this->fullBodyClassifier.empty() << std::endl;

    this->fullBodyClassifier.load("/Users/emmariedl/Desktop/Alten_C++/Projekt/machine-vision/peopleDetection/haarcascade_fullbody.xml");

    std::cout << "Classifier: " << this->fullBodyClassifier.empty() << std::endl;
    //this->upperBodyClassifier.load("haarcascade_upperbody.xml");
    //this->lowerBodyClassifier.load("haarcascade_lowerbody.xml");
}

void cascadeDetection::setFrame(cv::Mat img)
{
    //cv::cvtColor(img, this->frame, cv::COLOR_BGR2GRAY);
    //this->frame = img;
    this->found.clear();
    this->levels.clear();
    this->weights.clear();
}

void cascadeDetection::detect()
{
    std::vector<cv::Rect> tempFound;
    std::vector<double> tempWeights;

    this->fullBodyClassifier.detectMultiScale(this->frame, this->found, this->levels, this->weights, 1.1, 3, 0, cv::Size(20,10), cv::Size(800,500), true);

    std::vector<int> indices;
    std::vector<float> confidences;

    for (auto i = 0; i < this->weights.size(); ++i)
    {
        confidences.push_back((float) this->weights[i]);
    }

    //Remove boxes that overlaps to much. Non Max Suppresion.
    cv::dnn::NMSBoxes(this->found, confidences, 0.2, 0.9, indices);


    if(!found.empty()){
        for (auto i = 0; i < indices.size(); ++i)
        {
            rectangle(this->fullsizeFrame,
                        this->found[indices[i]].tl()*2, this->found[indices[i]].br()*2,
                        cv::Scalar(0, 255, 0), 2);
        }
    }

    this->sendQImage();
}

void cascadeDetection::recieveImage(cv::Mat img)
{
    cv::resize(img, this->frame, cv::Size(img.size()/2), 0, 0, cv::INTER_NEAREST);
    this->setFrame(this->frame);
    this->fullsizeFrame = img;

    this->detect();
}


