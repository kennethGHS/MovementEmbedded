//
// Created by kenneth on 5/6/21.
//

#ifndef UNTITLED1_HTTPREQUESTS_H
#define UNTITLED1_HTTPREQUESTS_H

#include <curl/curl.h>
#include <iostream>

using namespace std;

class HttpRequests {
public:
    static int sendPicture(string filename);
    static int sendTrueStatus();
    static int sendFalseStatus();
    static int sendPipeline(string pipe);
};


#endif //UNTITLED1_HTTPREQUESTS_H
