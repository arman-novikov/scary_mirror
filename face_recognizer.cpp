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
        const cv::Mat& frame, double factor, int extra)
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
        const int width = static_cast<int>((face.width + extra)/factor);
        const int height = static_cast<int>((face.height + extra)/factor);
        int x = static_cast<int>((face.tl().x - extra)/factor);
        int y = static_cast<int>((face.tl().y - extra)/factor);
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        cv::Rect face_area_on_orig_frame(x, y, width, height);
        res.push_back(frame(face_area_on_orig_frame));
    }
    return res;
}

/*
 * @warning no preparing work done
*/

void FaceRecognizer::getFaceAttr(
        const cv::Mat& frame, std::vector<FaceAttr>& res,
        double factor)
{
    MSEstimator estimator("getFaceAttr done, ");
    std::vector<cv::Rect> faces{}, eyes{};
    cv::Mat prepared_frame;

    cv::cvtColor(frame, prepared_frame, cv::COLOR_BGR2GRAY);
    cv::resize(prepared_frame, prepared_frame,
               cv::Size(), factor, factor, cv::INTER_LINEAR);
    cv::equalizeHist(prepared_frame, prepared_frame);

    // @todo: use 3 for @param minNeighbors
    // @todo: check _face_cascade on emptiness
    this->_face_cascade.detectMultiScale(
        prepared_frame, faces,
        1.1, 2, cv::CASCADE_SCALE_IMAGE, cv::Size(100,100));


    for (const auto& face: faces) {
        const int x = static_cast<int>(face.tl().x/factor);
        const int y = static_cast<int>(face.tl().y/factor);
        const int width = static_cast<int>(face.width/factor);
        const int height = static_cast<int>(face.height/factor);
        FaceAttr fattr;
        cv::Rect face_area_on_orig_frame(x, y, width, height);
        fattr.face = frame(face_area_on_orig_frame);

        this->_eyes_cascade.detectMultiScale(
            prepared_frame, eyes,
            1.1, 2, cv::CASCADE_SCALE_IMAGE, cv::Size(25,25)
        );

        for (const auto &eye: eyes) {
            const int x = static_cast<int>(eye.tl().x/factor);
            const int y = static_cast<int>(eye.tl().y/factor);
            const int width = static_cast<int>(eye.width/factor);
            const int height = static_cast<int>(eye.height/factor);
            cv::Rect eye_area_on_orig_frame(x, y, width, height);
            fattr.eyes.push_back(frame(eye_area_on_orig_frame));
        }
        res.push_back(fattr);
    }
}
