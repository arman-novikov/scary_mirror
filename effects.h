#pragma once
#include "opencv2/imgproc.hpp"

void make_zombie(cv::Mat& face);
void make_pale(cv::Mat& face, double gamma = 0.3);
