#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H


class FaceRecognizer
{
public:
    FaceRecognizer();
    std::vector<dlib::image_window::overlay_line> calculateOverlay(std::vector<dlib::full_object_detection> shapes);
};

#endif // FACERECOGNIZER_H
