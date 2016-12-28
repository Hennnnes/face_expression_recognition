#include "copyprocessor.h"

#include <QDebug>

using namespace cv;

CopyProcessor::CopyProcessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void CopyProcessor::startProcessing(const VideoFormat& format){

}

// wird für jedes Videoframe aufgerufen
cv::Mat CopyProcessor::process(const cv::Mat&source){
   // Mat copyOfSource;
    // source.copyTo(copyOfSource);
    // return copyOfSource;

    qDebug() << "test";

    Mat output = qtProcess(source);

    return output;
}


// wird für jedes Videoframe aufgerufen
cv::Mat CopyProcessor::qtProcess(const cv::Mat&source){


    return source;
}
