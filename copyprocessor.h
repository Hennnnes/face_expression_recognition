#ifndef COPYPROCESSOR_H
#define COPYPROCESSOR_H

#include "videoprocessor.h"

class CopyProcessor : public VideoProcessor
{
public:
    CopyProcessor();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    cv::Mat qtProcess(const cv::Mat&source);
};

#endif // COPYPROCESSOR_H
