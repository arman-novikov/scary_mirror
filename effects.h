#pragma once
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"

void mat_fill(cv::Mat& mat, const cv::Vec3b& color = {0,255,0});
void make_zombie(cv::Mat& orig_face, cv::Mat zombie_face);
void make_pale(cv::Mat& face, double gamma = 0.3);
void alpha_blend();
