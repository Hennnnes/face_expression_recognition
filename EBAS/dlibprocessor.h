#ifndef DLIBPROCESSOR_H
#define DLIBPROCESSOR_H

#include "videoprocessor.h"
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#include <qDebug>
#include <facerecognizer.h>
#include "audiocontroller.h"

using namespace dlib;


class Dlibprocessor : public VideoProcessor
{
public:
    Dlibprocessor();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    int recognizeFace(cv::Mat source);
    void setAudioController(AudioController *ac);
private:
    frontal_face_detector detector;
    shape_predictor pose_model;
    std::vector<int> tenEmotions;
    AudioController *ac;
};

#endif // DLIBPROCESSOR_H
