#pragma once
#include <chrono>

class MSEstimator
{
public:
    MSEstimator();
    void get_elapsed();
    ~MSEstimator();
private:
    std::chrono::time_point<std::chrono::system_clock> _ts;
    bool _is_estimation_done;
};
