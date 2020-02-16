#include "face_recognizer.h"
#include "msestimator.h"

FaceRecognizer::FaceRecognizer(
        const std::string& haarcascade_face,
        const std::string& haarcascade_eyes):
    _face_cascade{}, _eyes_cascade{}
{
    this->_face_cascade.load(haarcascade_face);
    this->_eyes_cascade.load(haarcascade_eyes);
}

mats_vec_t FaceRecognizer::getFaceROI(
        const cv::Mat& frame, double factor)
{
    MSEstimator estimator;
    std::vector<cv::Rect> faces;
    cv::Mat prepared_frame;
    mats_vec_t res;

    cv::cvtColor(frame, prepared_frame, cv::COLOR_BGR2GRAY);
    cv::resize(prepared_frame, prepared_frame,
               cv::Size(), factor, factor, cv::INTER_LINEAR);
    cv::equalizeHist(prepared_frame, prepared_frame);

    // @todo: use 3 for @param minNeighbors
    // @todo: check _face_cascade on emptiness
    this->_face_cascade.detectMultiScale(
        prepared_frame, faces,
        1.1, 2, cv::CASCADE_SCALE_IMAGE, cv::Size(100,100));

std::cerr << faces.size() << " faces found, ";
estimator.get_elapsed();
std::cerr << std::endl;

    for (const auto& face: faces) {
        const int x = static_cast<int>(face.tl().x/factor);
        const int y = static_cast<int>(face.tl().y/factor);
        const int width = static_cast<int>(face.width/factor);
        const int height = static_cast<int>(face.height/factor);
        cv::Rect face_area_on_orig_frame(x, y, width, height);
        res.push_back(frame(face_area_on_orig_frame));
    }
    return res;
}
