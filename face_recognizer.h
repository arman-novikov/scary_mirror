#pragma once

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <vector>
#include <string>

using mats_vec_t = std::vector<cv::Mat>;
class FaceRecognizer {
public:
    FaceRecognizer(const std::string& haarcascade_face,
                   const std::string& haarcascade_eyes);
    mats_vec_t getFaceROI(const cv::Mat& frame, double factor = 1.0);
protected:
    cv::CascadeClassifier _face_cascade;
    cv::CascadeClassifier _eyes_cascade;
};
