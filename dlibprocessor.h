#ifndef DLIBPROCESSOR_H
#define DLIBPROCESSOR_H

#include "videoprocessor.h"

class Dlibprocessor : public VideoProcessor
{
public:
    Dlibprocessor();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    cv::Mat qtProcess(const cv::Mat&source);
};

#endif // DLIBPROCESSOR_H
