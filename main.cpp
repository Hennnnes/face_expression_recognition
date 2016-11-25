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

using namespace dlib;
using namespace std;

int main()
{
    try
    {
        cv::VideoCapture cap(0);

        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

      //  cap.set(CV_CAP_PROP_FRAME_WIDTH, 160);
      //  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 120);

        image_window win;

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;

        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Grab and process frames until the main window is closed by the user.
        short count = 0;
        while(!win.is_closed())
        {

            // schleife erstmal nur für einen Frame ausführen
            if (count == 0){
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


                // Display it all on the screen
                win.clear_overlay();
                win.set_image(cimg);


                // calculate overlay
                const rgb_pixel color = rgb_pixel(255,255,0);
                std::vector<image_window::overlay_line> lines;
                for (unsigned long i = 0; i < shapes.size(); ++i)
                {
                    DLIB_CASSERT(shapes[i].num_parts() == 68,
                        "\t std::vector<image_window::overlay_line> render_face_detections()"
                        << "\n\t Invalid inputs were given to this function. "
                        << "\n\t shapes["<<i<<"].num_parts():  " << shapes[i].num_parts()
                    );

                    const full_object_detection& d = shapes[i];
                    // Around Chin. Ear to Ear
                  /*  for (unsigned long i = 1; i <= 16; ++i) {
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    }
                  */
                  /*
                    // Line on top of nose
                    for (unsigned long i = 28; i <= 30; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                  */
                  /*
                    // left eyebrow
                    for (unsigned long i = 18; i <= 21; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    // Right eyebrow
                    for (unsigned long i = 23; i <= 26; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    // Bottom part of the nose
                    for (unsigned long i = 31; i <= 35; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    // Line from the nose to the bottom part above
                    lines.push_back(image_window::overlay_line(d.part(30), d.part(35), color));
                */
                    /*
                    // Left eye
                    for (unsigned long i = 37; i <= 41; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    lines.push_back(image_window::overlay_line(d.part(36), d.part(41), color));

                    // Right eye
                    for (unsigned long i = 43; i <= 47; ++i)
                        lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    lines.push_back(image_window::overlay_line(d.part(42), d.part(47), color));
                */
                    // Lips outer part
                    for (unsigned long i = 49; i <= 59; ++i) {
                        // lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    }

                    lines.push_back(image_window::overlay_line(d.part(49), d.part(48), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(50), d.part(49), rgb_pixel(255,0,125)));
                    lines.push_back(image_window::overlay_line(d.part(51), d.part(50), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(52), d.part(51), rgb_pixel(255,0,125)));
                    lines.push_back(image_window::overlay_line(d.part(53), d.part(52), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(54), d.part(53), rgb_pixel(255,0,125)));

                    lines.push_back(image_window::overlay_line(d.part(55), d.part(54), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(56), d.part(55), rgb_pixel(255,0,125)));
                    lines.push_back(image_window::overlay_line(d.part(57), d.part(56), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(58), d.part(57), rgb_pixel(255,0,125)));
                    lines.push_back(image_window::overlay_line(d.part(59), d.part(58), rgb_pixel(0,100,255)));
                    lines.push_back(image_window::overlay_line(d.part(48), d.part(59), rgb_pixel(255,0,125)));
                    // end Lips outer Part

                    // line from one end to the other
                    lines.push_back(image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(200,200,200)));


                    // Lips inside part
                    for (unsigned long i = 61; i <= 67; ++i) {
                      //  lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
                    }
                    lines.push_back(image_window::overlay_line(d.part(61), d.part(60), rgb_pixel(120,120,255)));
                    lines.push_back(image_window::overlay_line(d.part(62), d.part(61), rgb_pixel(255,0,0)));
                    lines.push_back(image_window::overlay_line(d.part(63), d.part(62), rgb_pixel(120,120,255)));
                    lines.push_back(image_window::overlay_line(d.part(64), d.part(63), rgb_pixel(255,0,0)));
                    lines.push_back(image_window::overlay_line(d.part(65), d.part(64), rgb_pixel(120,120,255)));
                    lines.push_back(image_window::overlay_line(d.part(66), d.part(65), rgb_pixel(255,0,0)));
                    lines.push_back(image_window::overlay_line(d.part(67), d.part(66), rgb_pixel(120,120,255)));

                    lines.push_back(image_window::overlay_line(d.part(60), d.part(67), rgb_pixel(255,0,0)));
                    // end Lips inside Part
                }

                // add overlay
                win.add_overlay(lines);

                count++;
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
