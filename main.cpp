#include "face_recognizer.h"
#include <iostream>
#include "opencv2/highgui.hpp"
#include <effects.h>

const std::string FACE_CASCADE {
    "/home/arman/haarcascades/haarcascade_frontalface_default.xml"
};

const std::string EYES_CASCADE {
    "/home/arman/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
};

int main(int, char**)
{
    const cv::Scalar FILL_COLOR {255, 0, 0};
    FaceRecognizer recognizer(FACE_CASCADE, EYES_CASCADE);
    cv::Mat photo = cv::imread("/home/arman/face.jpg", CV_LOAD_IMAGE_COLOR);
    mats_vec_t faces = recognizer.getFaceROI(photo);

    //for (auto& i: faces)
    //    make_zombie(i);
    make_zombie(photo);


    cv::imshow("Face Detection", photo);
    cv::waitKey(0);
}
