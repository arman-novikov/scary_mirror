#pragma once
#include "opencv2/imgproc.hpp"

void mat_fill(cv::Mat& mat, const cv::Vec3b& color = {0,255,0});
void make_zombie(cv::Mat& face);
void make_pale(cv::Mat& face, double gamma = 0.3);
