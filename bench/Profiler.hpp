#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <iostream>
#include <vector>

using namespace std::chrono;
using namespace std;

class Profiler {
   private:
    vector<int> numbers;
    vector<steady_clock::time_point> startTimes;
    vector<steady_clock::time_point> stopTimes;

   public:
    // functions that take one int arguement and return void
    using FuncType = void(int);
    void start(int n);
    void stop();
    void dump();
    void AlgorithmProfiler(FuncType &);
};

void Profiler::start(int n) {
    numbers.push_back(n);
    startTimes.push_back(steady_clock::now());
}

void Profiler::stop() { stopTimes.push_back(steady_clock::now()); }

void Profiler::dump() {
    cout<<"-- n --|----- time ---------------" << endl;
    duration<double, std::milli> time_span;
    for (int i = 0; i < numbers.size(); i++) {
        printf("%-8d ", numbers[i]);
        time_span = duration_cast<duration<double, std::milli>>(
            stopTimes.at(i) - startTimes.at(i));
        cout << time_span.count() << " ms" << endl;
    }
}

void Profiler::AlgorithmProfiler(FuncType &func) {
    steady_clock::time_point t1 = steady_clock::now();

    std::cout << "running n = 1000..." << std::endl;
    func(1000);

    steady_clock::time_point t2 = steady_clock::now();

    duration<double, std::milli> time_span =
        duration_cast<duration<double, std::milli>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " milliseconds.";
    std::cout << std::endl;
}

#endif  // PROFILER_HPP
