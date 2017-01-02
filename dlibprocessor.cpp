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
    String text = "Sad";
    int fontFace = FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;


    Mat output;
    source.copyTo(output);
    //rectangle(output, Point(0,0), Point(100, 100), Scalar(0, 200, 200), 3);


    int baseline=0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;

    // then put the text itself
    putText(output, text, Point(50, 50), fontFace, fontScale,
            Scalar(0, 0, 255), thickness, 8);

    return output;
}
