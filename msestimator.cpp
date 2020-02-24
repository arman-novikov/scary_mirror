#include "msestimator.h"
#include <iostream>

using namespace std;

MSEstimator::MSEstimator(std::string msg):
    _msg(msg),
    _ts(chrono::system_clock::now()),
    _is_estimation_done(false)
{}

void MSEstimator::get_elapsed()
{
    const auto now = chrono::system_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(now - this->_ts);
std::cerr << this->_msg << ms.count() << " ms elapsed" << std::endl;
    this->_is_estimation_done = true;
}

MSEstimator::~MSEstimator()
{
    if (!this->_is_estimation_done)
        this->get_elapsed();
}
