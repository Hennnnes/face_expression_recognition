#include "dlibprocessor.h"

using namespace cv;

Dlibprocessor::Dlibprocessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void Dlibprocessor::startProcessing(const VideoFormat& format){

}

// wird für jedes Videoframe aufgerufen
cv::Mat Dlibprocessor::process(const cv::Mat&source){

    return source;
}
