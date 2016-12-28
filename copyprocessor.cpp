#include "copyprocessor.h"

#include <QDebug>


// includes for dlib
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
// end dlib includes

using namespace cv;

// dlib namespaces
using namespace dlib;
using namespace std;
// end dlib namespaces

frontal_face_detector detector;
shape_predictor pose_model;

CopyProcessor::CopyProcessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void CopyProcessor::startProcessing(const VideoFormat& format){
    frontal_face_detector detector = get_frontal_face_detector();

    deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
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


    // now for each frame, fixed later
            // Load face detection and pose estimation models.

    // end now for each frame

    // dlib function from videocapturer.cpp
        cv::Mat temp;
        source.copyTo(temp);

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
    // end dlib function from videocapturer.cpp

    // calculate overlay originally from facerecognizer.cpp fucntion calculateOverlay()
        std::vector<image_window::overlay_line> lines;
            for (unsigned long i = 0; i < shapes.size(); ++i)
            {
                DLIB_CASSERT(shapes[i].num_parts() == 68,
                    "\t std::vector<image_window::overlay_line> render_face_detections()"
                    << "\n\t Invalid inputs were given to this function. "
                    << "\n\t shapes["<<i<<"].num_parts():  " << shapes[i].num_parts()
                );

                const full_object_detection& d = shapes[i];

                // lips outer part
                for (int i = 49; i < 59; ++i) {
                    lines.push_back(dlib::image_window::overlay_line(d.part(i), d.part(i - 1), rgb_pixel(0,100,255)));
                }

                lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(59), rgb_pixel(255,0,125)));
                // end Lips outer Part

                // line from one end to the other
                //lines.push_back(image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(200,200,200)));


                // Lips inside part
                for (int i = 61; i <= 67; ++i) {
                   lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), rgb_pixel(120,120,255)));
                }

                lines.push_back(dlib::image_window::overlay_line(d.part(60), d.part(67), rgb_pixel(255,0,0)));
                // end Lips inside Part


                // read left and right point, WARUM 0,500???
                // dachte an hoffentlich groß genug damit der punkt immer überschrieben wird
                point upper = point(0,1000);
                point lower = point(0,0);

                for ( int i = 48; i < 68; i++) {
                    if (d.part(i).y() > lower.y()){
                        lower = d.part(i);
                    }
                    if (d.part(i).y() < upper.y()){
                        upper = d.part(i);
                    }
                }

                // Mouthheight
                long mh = (lower.y() - upper.y());

                //lipheight average
                long lipheight = (d.part(48).y() - upper.y() + d.part(54).y() - upper.y())/2;

                lines.push_back(dlib::image_window::overlay_line(upper, d.part(48), rgb_pixel(255,255,255)));

                if ( mh/2 >= (1.35 * lipheight) ) {
                    // glücklich
                    qDebug() << "glücklich";
                    lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(0,0,255)));
                } else if ( mh / 2 < (1 * lipheight) ) {
                    // traurig
                    qDebug() << "traurig";
                    lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(255,100,0)));
                } else {
                    // neutral
                    qDebug() << "neutral";
                    lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(255,255,255)));
                }

            }
    // end calculate overlay



    return temp;
}
