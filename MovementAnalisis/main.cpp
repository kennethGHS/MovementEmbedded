#include "./lib/MovementAnalizer.h"
#include "./lib/HttpRequests.h"
using namespace std;
//gst-launch-1.0 -v v4l2src \
// ! video/x-raw,format=YUY2,width=640,height=480 \
// ! jpegenc \
// ! rtpjpegpay \
// ! udpsink host=127.0.0.1 port=5000

#include<ctime> // used to work with date and time
#include <iostream>
#include <thread>
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
void execute(){
    MovementAnalyzer *movementAnalyzer = new MovementAnalyzer(
            "udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
            30, false);
    movementAnalyzer->analyzeImages();
}
int main(int argc, char *argv[]) {
//    time_t t; // t passed as argument in function time()
//    struct tm * tt; // decalring variable for localtime()
//    time (&t); //passing argument to time()
//    tt = localtime(&t);
//    cout << tt->tm_sec ;
    HttpRequests::sendTrueStatus();
    HttpRequests::sendPipeline("udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink");
    thread t1(execute);

    while (true) {}

}