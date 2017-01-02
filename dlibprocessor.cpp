#include "dlibprocessor.h"

#include "videocapturer.h"

using namespace dlib;
using namespace std;
using namespace cv;

Dlibprocessor::Dlibprocessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void Dlibprocessor::startProcessing(const VideoFormat& format){
    detector = get_frontal_face_detector();
    deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
}

// wird für jedes Videoframe aufgerufen
cv::Mat Dlibprocessor::process(const cv::Mat&source){
    String text = "Sad";
    int fontFace = FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;


    Mat output;
    source.copyTo(output);

    recognizeFace(output);
    //rectangle(output, Point(0,0), Point(100, 100), Scalar(0, 200, 200), 3);


    int baseline=0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;

    // then put the text itself
    putText(output, text, Point(50, 50), fontFace, fontScale,
            Scalar(0, 0, 255), thickness, 8);

    return output;
}


void Dlibprocessor::recognizeFace(cv::Mat temp) {
    // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
    // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
    // long as temp is valid.  Also don't do anything to temp that would cause it
    // to reallocate the memory which stores the image as that will make cimg
    // contain dangling pointers.  This basically means you shouldn't modify temp
    // while using cimg.
    cv_image<bgr_pixel> cimg(temp);

    // Detect faces
    std::vector<dlib::rectangle> faces = detector(cimg);

    // Find the pose of each face.
    std::vector<full_object_detection> shapes;
    for (unsigned long i = 0; i < faces.size(); ++i) {
        shapes.push_back(pose_model(cimg, faces[i]));
    }

    // calculate overlay
    FaceRecognizer recog = FaceRecognizer();
    std::vector<image_window::overlay_line> lines = recog.calculateOverlay(shapes);

    if(tenEmotions.size() >= 20) {
        tenEmotions.erase(tenEmotions.begin());
    }

    tenEmotions.push_back(recog.getEmotion());

    int happy = 0;
    int neutral = 0;
    int sad = 0;

    for(int i = 0; i < tenEmotions.size(); i++) {
        //qDebug() << tenEmotions[i];
        if(tenEmotions[i] == 0) {
            neutral++;
        } else if (tenEmotions[i] == 1){
            happy++;
        } else if (tenEmotions[i] == 2) {
            sad++;
        }
    }

    qDebug() << happy << neutral << sad ;

    if (happy >= sad) {
        if(happy >= neutral){
            qDebug() << "emotion: glücklich";
        } else {
            qDebug() << "emotion: neutral";
        }

    } else if (sad >= neutral) {
        qDebug() << "emotion: traurig";

    } else {
        qDebug() << "emotion: neutral";
    }

}
