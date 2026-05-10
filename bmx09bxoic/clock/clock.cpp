#include "clock.h"

void ClockInstance::updateTime()
{
    const std::unique_lock<std::mutex> lock(mtx);
    now = std::chrono::high_resolution_clock::now();
}

std::chrono::steady_clock::time_point ClockInstance::getTime()
{
    const std::unique_lock<std::mutex> lock(mtx);
    return now;
}

ClockInstance& getClockInstance()
{
    static ClockInstance ptr;
    return ptr;
}
