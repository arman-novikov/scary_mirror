#include "effects.h"
#include "msestimator.h"
#include <cstdlib>
#include <vector>

void make_zombie(cv::Mat& face)
{
    MSEstimator estimator;
    auto it = face.begin<cv::Vec3b>();
    const auto end = face.end<cv::Vec3b>();
    const std::vector<cv::Scalar> zombie_colors {
        {0xc6, 0xbf, 0x2d},
        {0xb5, 0xaf, 0x37},
        {0xab, 0xa3, 0x11},
        {0xc6, 0xbf, 0x2d},
        {0xbf, 0xb8, 0x3d},
        {0xa7, 0xd3, 0x58},
        {0x83, 0xb2, 0x2f},
    };

    std::srand(unsigned(std::time(0)));
     //uchar b,g,r;
    //cv::bitwise_not(face, face);
    for (; it != end; ++it) {
        auto& b = (*it)[0];
        auto& g = (*it)[1];
        auto& r = (*it)[2];

        const uchar avr = (b + g + r) / 3;


        g += g < 200? 50: 250 - g;
        if (r > 150 && g < 180 && b < 100) {
            r = b = g = avr;
        }

        int rand_val = std::rand();
        if (rand_val%3==0) {
            b = zombie_colors[rand_val%zombie_colors.size()][2];
            r = zombie_colors[rand_val%zombie_colors.size()][0];
        }
        //r *= 0.3;
    }
}
