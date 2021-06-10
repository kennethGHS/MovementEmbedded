//
// Created by kenneth on 5/6/21.
//

#include <sys/stat.h>
#include <cstring>
#include "../lib/HttpRequests.h"

int HttpRequests::sendPicture(string filename) {
    printf("Uploading \n");
    CURL *curl;
    CURLcode res;
    struct stat file_info;
    curl_off_t speed_upload, total_time;
    FILE *fd;
    struct stat st = {0};

    if (stat("../Image", &st) == -1) {
        mkdir("../Image", 0777);
    }

    fd = fopen("../Image/newPicture.jpg", "rb"); /* open file to upload */
    if (!fd)
        return 1; /* can't continue */


    if (fstat(fileno(fd), &file_info) != 0)
        return 1;

    curl = curl_easy_init();
    printf("test");
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL,
                         "http://127.0.0.1:8000/api/picture");

        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_READDATA, fd);

        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                         (curl_off_t) file_info.st_size);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        } else {
            curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);

            fprintf(stderr, "Speed: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
                            CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
                    speed_upload,
                    (total_time / 1000000), (long) (total_time % 1000000));

        }
        curl_easy_cleanup(curl);
    }
    fclose(fd);
    return 0;
}

int HttpRequests::sendTrueStatus() {
    CURL *curl;
    CURLcode res;

    string post_json = "True";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/status");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_json.data());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_json.size());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return -1;
        }
    }
    curl_easy_cleanup(curl);
    return 0;
}

int HttpRequests::sendFalseStatus() {
    CURL *curl;
    CURLcode res;

    string post_json = "False";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/status");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_json.data());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_json.size());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return -1;
        }
    }
    curl_easy_cleanup(curl);
    return 0;
}

int HttpRequests::sendPipeline(string pipe) {
    CURL *curl;
    CURLcode res;

    string post_json = pipe;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/pipe");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_json.data());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_json.size());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return -1;
        }
    }
    curl_easy_cleanup(curl);
    return 0;
}
