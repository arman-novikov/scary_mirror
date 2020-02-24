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
void make_zombie(cv::Mat& face)
{
    MSEstimator estimator("make_zombie done, ");
    make_pale(face);
}

void make_pale(cv::Mat& face, double gamma)
{
    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();

    for( int i = 0; i < 256; ++i)
        p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

   cv::LUT(face, lookUpTable, face);
}
