#include "copyprocessor.h"

using namespace cv;

CopyProcessor::CopyProcessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void CopyProcessor::startProcessing(const VideoFormat& format){

}

// wird für jedes Videoframe aufgerufen
cv::Mat CopyProcessor::process(const cv::Mat&source){
    Mat copyOfSource;
    source.copyTo(copyOfSource);
    return copyOfSource;
}
