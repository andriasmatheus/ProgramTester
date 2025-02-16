#ifndef CMONITOR_H
#define CMONITOR_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>

template<typename TypeOfTimer>
class CMonitor
{
public:
    CMonitor(void) {}

    template<typename T, typename... Args>
    T Monitorate(T(*pFunction)(Args...), Args... args)
    {
        constexpr int min_repetitions = 5;
        constexpr auto min_duration = TypeOfTimer(100);
    
        int count = 0;
        auto total_duration = TypeOfTimer::zero();
        T out = T();
    
        while (count < min_repetitions || total_duration < min_duration)
        {
            auto start = std::chrono::steady_clock::now();
            out = pFunction(args...);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_nanoseconds = std::chrono::duration_cast<TypeOfTimer>(end - start);
    
            total_duration += elapsed_nanoseconds;
            ++count;
        }
    
        auto average = total_duration / count;
        std::cout << "Elapsed time: " << average.count() <<  std::endl;
        return out;
    }
};

#endif //CMONITOR_H