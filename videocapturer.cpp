#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>


#include <qDebug>
#include <facerecognizer.h>

#include "videocapturer.h"


using namespace dlib;
using namespace std;

VideoCapturer::VideoCapturer()
{

}

void VideoCapturer::start(cv::VideoCapture cap) {
    try
    {
        // videocapture
        //cv::VideoCapture cap(0);

        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            exit;
        }

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;

        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;


        // init last emotions array
        std::list<int> emotionlist;


        // Grab and process frames until the main window is closed by the user.
        while(true)
        {
                // Grab a frame
                cv::Mat temp;
                cap >> temp;
                // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
                // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
                // long as temp is valid.  Also don't do anything to temp that would cause it
                // to reallocate the memory which stores the image as that will make cimg
                // contain dangling pointers.  This basically means you shouldn't modify temp
                // while using cimg.
                cv_image<bgr_pixel> cimg(temp);

                // Detect faces
                std::vector<rectangle> faces = detector(cimg);

                // Find the pose of each face.
                std::vector<full_object_detection> shapes;
                for (unsigned long i = 0; i < faces.size(); ++i) {
                    shapes.push_back(pose_model(cimg, faces[i]));
                }

                // calculate overlay
                FaceRecognizer recog = FaceRecognizer();
                std::vector<image_window::overlay_line> lines = recog.calculateOverlay(shapes);

                int emotion = recog.getEmotion();

                if (emotion == 1) {
                    qDebug() << "emotion: glücklich";

                } else if (emotion == 0) {
                    qDebug() << "emotion: neutral";

                } else if (emotion == 2) {
                    qDebug() << "emotion: traurig";

                }
        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}
