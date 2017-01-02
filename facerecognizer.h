#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H


class FaceRecognizer
{
public:
    int emotion;
    FaceRecognizer();
    int getEmotion(std::vector<dlib::full_object_detection> shapes);
};

#endif // FACERECOGNIZER_H
