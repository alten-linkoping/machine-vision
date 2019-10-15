#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>

#include "opticalflow.h"
#include "hogdetection.h"
#include "cascadedetection.h"

class Player : public QThread
{   Q_OBJECT

private:
    detector *detector = new opticalFlow();

    bool stop;
    cv::VideoCapture cap;
    cv::Mat frame;
    cv::Mat RGBframe;
    int frameRate;
    QImage QFrame;
    QMutex mutex;
    QWaitCondition condition;
    QImage detectionImage;
    QString detectorName;

private slots:
    void recieveProcessedImage(QImage img);

signals:
    void processedImage(const QImage &image);
    void imageMat(const cv::Mat &image);

protected:
    void run();
    void msleep(int ms);

public:
    //Constructor
    Player(QObject *parent = nullptr);
    //Destructor
    ~Player();
    //Load a video from memory
    bool loadVideo(std::string filename);
    void Play();
    bool isStopped() const;
    void Stop();
    void setDetector(QString detectorName);
};

#endif // PLAYER_H
