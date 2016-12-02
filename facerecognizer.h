#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H


class FaceRecognizer
{
public:
    int emotion;
    FaceRecognizer();
    std::vector<dlib::image_window::overlay_line> calculateOverlay(std::vector<dlib::full_object_detection> shapes);
    int getEmotion();
};

#endif // FACERECOGNIZER_H
