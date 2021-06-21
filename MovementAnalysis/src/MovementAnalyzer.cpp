//
// Created by kenneth on 2/6/21.
//

#include <sys/stat.h>
#include "../lib/MovementAnalyzer.h"
#include "../lib/HttpRequests.h"

extern "C" {
    #include "../lib/gpio.h"
}

MovementAnalyzer::MovementAnalyzer(const string pipe, int intervalS, bool detected) : pipe(pipe),
                                                                                       frame_intervals(intervalS),
                                                                                       detected(detected) {
    this->capture = new VideoCapture(pipe,CAP_GSTREAMER);
    this->pBackSub = createBackgroundSubtractorMOG2();
    if (!this->capture->isOpened()){
        //error in opening the video input
        cerr << "Unable to open: " << endl;
    }
    this->semaphore = static_cast<sem_t *>(malloc(sizeof(sem_t)));

    sem_init(semaphore, 0, 1);
}

const string &MovementAnalyzer::getPipe() const {
    return pipe;
}

void MovementAnalyzer::setPipe(const string &pipe) {
    MovementAnalyzer::pipe = pipe;
}

int MovementAnalyzer::getTime(){
    time_t t; // t passed as argument in function time()
    struct tm * tt; // decalring variable for localtime()
    time (&t); //passing argument to time()
    tt = localtime(&t);
    return tt->tm_sec ;
}

void MovementAnalyzer::setIntervalS(int intervalS) {
    frame_intervals = intervalS;
}

void MovementAnalyzer::setDetected(bool detected) {
    sem_wait(semaphore);
    MovementAnalyzer::detected = detected;
    sem_post(semaphore);
}

int MovementAnalyzer::getIntervalS() const {
    return frame_intervals;
}

bool MovementAnalyzer::isDetected() const {
    sem_wait(semaphore);
    bool state = this->detected;
    sem_post(semaphore);
    return state;
}

void MovementAnalyzer::analyzeImages() {
    int frameCount = 0;
    Mat frame, fgMask;
    int movements = 0;
    initSevenSegmentDisplay(2, 3, 4, 5, 6, 7, 8);
    while (true) {
        frameCount+=1;

        *this->capture >> frame;
        if (frame.empty())
            break;
        pBackSub->apply(frame, fgMask,-1);
        if (frameCount != frame_intervals){
            continue;
        }
        frameCount = 0;
        HttpRequests::sendTrueStatus();
        RNG rng(12345);
        findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE,Point(0, 0));

        vector<Rect>boundRect (contours.size());
        vector<vector<Point> > contours_poly( contours.size() );
        sevenSegmentWrite('0');
        for (int i = 0; i < contours.size();i++) {
            if( contourArea(contours[i])< 500)
            {
                continue;
            }
            putText(frame, "Motion Detected", Point(10,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
            approxPolyDP( contours[i], contours_poly[i], 3, true );
            boundRect[i] = boundingRect( contours_poly[i] );
            Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
            rectangle( frame, boundRect[i].tl(), boundRect[i].br(), color, 2 );
            struct stat st = {0};
            if (stat("../Image", &st) == -1) {
                mkdir("../Image", 0777);
            }
            string filename = "../Image/newPicture.jpg";
            imwrite(filename,frame);
            HttpRequests::sendPicture(filename);
            if (movements >= 10){
                movements = 0;
            }

            sevenSegmentWrite('0'+movements);

	    }
	

    }
}
