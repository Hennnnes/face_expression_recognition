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
{

}


std::vector<image_window::overlay_line> FaceRecognizer::calculateOverlay(std::vector<full_object_detection> shapes) {

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
        lines.push_back(dlib::image_window::overlay_line(d.part(49), d.part(48), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(50), d.part(49), rgb_pixel(255,0,125)));
        lines.push_back(dlib::image_window::overlay_line(d.part(51), d.part(50), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(52), d.part(51), rgb_pixel(255,0,125)));
        lines.push_back(dlib::image_window::overlay_line(d.part(53), d.part(52), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(54), d.part(53), rgb_pixel(255,0,125)));

        lines.push_back(dlib::image_window::overlay_line(d.part(55), d.part(54), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(56), d.part(55), rgb_pixel(255,0,125)));
        lines.push_back(dlib::image_window::overlay_line(d.part(57), d.part(56), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(58), d.part(57), rgb_pixel(255,0,125)));
        lines.push_back(dlib::image_window::overlay_line(d.part(59), d.part(58), rgb_pixel(0,100,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(59), rgb_pixel(255,0,125)));
        // end Lips outer Part

        // line from one end to the other
        //lines.push_back(image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(200,200,200)));


        // Lips inside part
        for (unsigned long i = 61; i <= 67; ++i) {
          //  lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(61), d.part(60), rgb_pixel(120,120,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(62), d.part(61), rgb_pixel(255,0,0)));
        lines.push_back(dlib::image_window::overlay_line(d.part(63), d.part(62), rgb_pixel(120,120,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(64), d.part(63), rgb_pixel(255,0,0)));
        lines.push_back(dlib::image_window::overlay_line(d.part(65), d.part(64), rgb_pixel(120,120,255)));
        lines.push_back(dlib::image_window::overlay_line(d.part(66), d.part(65), rgb_pixel(255,0,0)));
        lines.push_back(dlib::image_window::overlay_line(d.part(67), d.part(66), rgb_pixel(120,120,255)));

        lines.push_back(dlib::image_window::overlay_line(d.part(60), d.part(67), rgb_pixel(255,0,0)));
        // end Lips inside Part


        // read left and right point, WARUM 0,500???
        point upper = point(0,0);
        point lower = point(0,500);

        for(int i = 48; i < 68; i++) {
            if(d.part(i).y() < lower.y()){
                lower = d.part(i);
            }
            if(d.part(i).y() > upper.y()){
                upper = d.part(i);
            }
        }

        long mh = (upper-lower).length();

        long lipheight = max(upper.y() - d.part(48).y(), upper.y() - d.part(54).y());
        if(mh/2 >= lipheight) {
            // neutral / traurig
            qDebug() << "neutral";
            lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(255,255,255)));
        } else {
            // glücklich
            qDebug() << "glücklich";
            lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(0,0,255)));
        }


        point secondPoint = point(100,100);
        point firstPoint = d.part(50);
    }

    return lines;
}
