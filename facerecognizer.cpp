// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.


    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#include <qDebug>

// include class header file
#include "facerecognizer.h"

using namespace dlib;
using namespace std;

FaceRecognizer::FaceRecognizer()
    : emotion(0)
{
}


int FaceRecognizer::getEmotion(std::vector<full_object_detection> shapes) {

    if (shapes.size() == 1) {

        DLIB_CASSERT(shapes[0].num_parts() == 68,
            "\t std::vector<image_window::overlay_line> render_face_detections()"
            << "\n\t Invalid inputs were given to this function. "
            << "\n\t shapes["<<0<<"].num_parts():  " << shapes[0].num_parts()
        );

        const full_object_detection& d = shapes[0];

        point upper = point(0,1000);
        point lower = point(0,0);

        for(int i = 48; i < 68; i++) {
            if (d.part(i).y() > lower.y()){
                lower = d.part(i);
            }
            if (d.part(i).y() < upper.y()){
                upper = d.part(i);
            }
        }

        // Mouthheight
        long mh = (lower.y() - upper.y());
        // qDebug() << upper.y();
        //lipheight average
        long lipheight = (d.part(48).y() - upper.y() + d.part(54).y() - upper.y())/2;
        // qDebug() << mh;
        if(mh/2 >= 1.35 *  lipheight) {
            // glücklich
            emotion = 1;

        } else if (mh / 2 < 0.8 * lipheight) {
            // traurig
            emotion = 2;

        } else {
            // neutral
            emotion = 0;

        }

        if (emotion != 1 && (d.part(66) - d.part(62)).y() > 0.8 * lipheight) {
            emotion = 3;
        }
    }
    else {
        emotion = -1;
    }


    return emotion;


}
