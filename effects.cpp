#include "effects.h"
#include "msestimator.h"
#include <cstdlib>
#include <vector>
#include <iostream>

void mat_fill(cv::Mat& mat, const cv::Vec3b& color)
{
    auto it = mat.begin<cv::Vec3b>();
    const auto end = mat.end<cv::Vec3b>();

    for (;it < end; ++it)
        *it = color;
}

/*
* @warning function is not finished
*/
void make_zombie(cv::Mat& orig_face, cv::Mat zombie_face)
{
    MSEstimator estimator("make_zombie done, ");
    const auto WIDTH = orig_face.size().width;
    const auto HEIGHT = orig_face.size().height;
    cv::resize(zombie_face, zombie_face,
               cv::Size(WIDTH, HEIGHT), 0.0, 0.0, cv::INTER_LINEAR);
    auto face_it = orig_face.begin<cv::Vec3b>();
    auto zombie_it = zombie_face.begin<cv::Vec3b>();
    const auto end = orig_face.end<cv::Vec3b>();

    for (;face_it < end; ++face_it, ++zombie_it) {
        int sum = 0;
        for (int i = 0; i < 3; ++i) {
            sum += (*zombie_it)[i];
        }
        if (sum >= 750)
            continue;
        *face_it = *zombie_it;
     }
}

void make_pale(cv::Mat& face, double gamma)
{
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();

    for( int i = 0; i < 256; ++i)
        p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

   cv::LUT(face, lookUpTable, face);
}

void alpha_blend()
{

}
