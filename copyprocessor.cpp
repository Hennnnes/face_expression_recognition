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

    Mat output(source.rows, source.cols, source.type());
        for(int x = 0; x < source.cols; x++){
            for(int y = 0; y < source.rows; y++){
                Vec3b inputPixel = source.at<Vec3b>(y,x);
                int r = inputPixel[2] + 20;
                int g = inputPixel[1] + 20;
                int b = 0;
                Vec3b outputPixel (b, g, r);    //= inputPixel + offset;//brightnessOffset;
                output.at<Vec3b>(y,x) = outputPixel;
            }
        }
    return output;
}
