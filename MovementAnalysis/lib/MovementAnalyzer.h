//
// Created by kenneth on 2/6/21.
//

#ifndef UNTITLED1_MOVEMENTANALYZER_H
#define UNTITLED1_MOVEMENTANALYZER_H
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <semaphore.h>
#include <thread>
using namespace std;
using namespace cv;
class MovementAnalyzer {
public:
    string pipe;
    int frame_intervals;
    bool detected;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    sem_t * semaphore;
    int getTime();

    const string &getPipe() const;

    int getIntervalS() const;

    bool isDetected() const;

    MovementAnalyzer(const string pipe, int intervalS, bool detected);

    void setPipe(const string &pipe);

    void setIntervalS(int intervalS);

    void setDetected(bool detected);

    void analyzeImages();

private:
    Ptr<BackgroundSubtractor> pBackSub;
    VideoCapture * capture;
    unsigned int movements;
};


#endif //UNTITLED1_MOVEMENTANALYZER_H
