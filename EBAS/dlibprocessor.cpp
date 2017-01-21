#include "dlibprocessor.h"

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
    //initialize Audiothread new audiothread(this);
}

// wird für jedes Videoframe aufgerufen
cv::Mat Dlibprocessor::process(const cv::Mat&source){
    String text = "abc";
    int fontFace = FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;


    Mat output;
    source.copyTo(output);


    int emotion = recognizeFace(output);
    //rectangle(output, Point(0,0), Point(100, 100), Scalar(0, 200, 200), 3);
    //if (!audiothread.playing)
    //audiothread.setEmotion(emotion)



    switch (emotion)
    {
    case -2:
        text = "No face found";
        break;
    case -1:
        text = "One face only please";
        break;
    case 0:
        text = "Sad";
        ac->setEmotion(2);
        break;
    case 1:
        text = "Neutral";
        ac->setEmotion(0);
        //ac->getMixer()->on(440,1,0);
        break;
    case 2:
        text = "Happy";
        ac->setEmotion(1);
        //ac->getMixer()->off(440,0);
        break;
    case 3:
        text = "Surprised";
        ac->setEmotion(3);
        break;
    default:
        text = "Default";
    }

    // then put the text itself
    putText(output, text, Point(50, 50), fontFace, fontScale,
            Scalar(0, 0, 255), thickness, 8);

    return output;
}


int Dlibprocessor::recognizeFace(cv::Mat temp) {
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

    if(tenEmotions.size() >= 10) {
        tenEmotions.erase(tenEmotions.begin());
    }

    tenEmotions.push_back(recog.getEmotion(shapes));


    int happy = 0;
    int neutral = 0;
    int sad = 0;
    int surprised = 0;
    int error = 0;
    int noFaceError = 0;

    for(int i = 0; i < tenEmotions.size(); i++) {
        //qDebug() << tenEmotions[i];
        if(tenEmotions[i] == 0) {
            neutral++;
        } else if (tenEmotions[i] == 1){
            happy++;
        } else if (tenEmotions[i] == 2) {
            sad++;
        } else if (tenEmotions[i] == 3) {
            surprised++;
        } else if (tenEmotions[i] == -1){
            error++;
        } else {
            return -2;
        }

    }

    //qDebug() << happy << neutral << sad ;
    int emotion = 1;

    if (happy >= sad && happy >= surprised && happy >= neutral && happy >= error)  {
        //qDebug() << "emotion: glücklich";
        emotion = 2;
    } else if (sad >= neutral && sad >= surprised && sad >= error) {
        //qDebug() << "emotion: traurig";
        emotion = 0;
    } else if (surprised >= neutral && surprised >= error){
        //qDebug() << "emotion: surprised";
        emotion = 3;
    } else if (error >= neutral) {
        emotion = -1;
    }

    return emotion;
}


void Dlibprocessor::setAudioController(AudioController *ac){
    this->ac = ac;
}
