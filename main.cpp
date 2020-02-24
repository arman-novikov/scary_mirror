#include "face_recognizer.h"
#include <iostream>
#include "opencv2/highgui.hpp"
#include <effects.h>

const std::string FACE_CASCADE {
    "/home/pi/haarcascades/haarcascade_frontalface_default.xml"
};

const std::string EYES_CASCADE {
    "/home/pi/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
};

[[noreturn]] [[maybe_unused]] static void test(const std::string& file_path);

int main(int, char**)
{
    const char winName[] = "scary_mirror";
    const cv::Scalar FILL_COLOR {255, 0, 0};
    FaceRecognizer recognizer(FACE_CASCADE, EYES_CASCADE);
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;

    if (!cap.open(0)) {
        std::cerr<<"coudn't open capture"<<std::endl;
        return -1;
    }

    for (cv::Mat frame;;) {
        std::vector<FaceAttr> fattrs{};
        cap >> frame;
        if (frame.empty())
            continue;
        recognizer.getFaceAttr(frame, fattrs);
        for (auto& fattr: fattrs) {
            mat_fill(fattr.face, {255, 0, 0});
            for (auto& eye: fattr.eyes) {
                mat_fill(eye, {0, 255, 0});
            }
        }
        cv::imshow(winName, frame);
        if (cv::waitKey(1) != 255) {
            std::cout<<"pressed "<<"\n";
            break;
        }
    }
}

static void test(const std::string& file_path)
{
    cv::Mat input = cv::imread(file_path, CV_LOAD_IMAGE_COLOR);
    FaceRecognizer recognizer(FACE_CASCADE, EYES_CASCADE);
    std::vector<FaceAttr> fattrs{};

    recognizer.getFaceAttr(input, fattrs);
    for (auto& fattr: fattrs) {
        mat_fill(fattr.face, {255, 0, 0});
        for (auto& eye: fattr.eyes) {
            mat_fill(eye, {0, 255, 0});
        }
    }

    cv::imshow("face detected", input);
    cv::waitKey(0);
    exit(0);
}
