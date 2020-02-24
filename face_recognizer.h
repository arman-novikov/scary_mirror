#pragma once

#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <vector>
#include <string>

using mats_vec_t = std::vector<cv::Mat>;

struct FaceAttr {
    cv::Mat face;
    mats_vec_t eyes;
};

class FaceRecognizer {
public:
    FaceRecognizer(const std::string& haarcascade_face,
                   const std::string& haarcascade_eyes);
    mats_vec_t getFaceROI(const cv::Mat& frame, double factor = 1.0);
    void getFaceAttr(
            const cv::Mat& frame, std::vector<FaceAttr>& res,
            double factor = 1.0);
protected:
    cv::CascadeClassifier _face_cascade;
    cv::CascadeClassifier _eyes_cascade;
};
