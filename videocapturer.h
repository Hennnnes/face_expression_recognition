#ifndef VIDEOCAPTURER_H
#define VIDEOCAPTURER_H

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>


class VideoCapturer
{
public:
    VideoCapturer();
    void start(cv::VideoCapture cap);
};

#endif // VIDEOCAPTURER_H
