#pragma once
#include <chrono>
#include <string>

class MSEstimator
{
public:
    MSEstimator(std::string msg="");
    void get_elapsed();
    ~MSEstimator();
private:
    std::string _msg;
    std::chrono::time_point<std::chrono::system_clock> _ts;
    bool _is_estimation_done;
};
