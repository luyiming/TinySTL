#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>

class Profiler {
   private:
    Profiler() = delete;

   public:
    using SteadyClock = std::chrono::steady_clock;
    using TimePoint = SteadyClock::time_point;
    using DurationTime = std::chrono::duration<double, std::ratio<1, 1>>;

   private:
    static DurationTime duringTime;
    static TimePoint startTime;
    static TimePoint stopTime;

   public:
    static void start();
    static void stop();
    static void dumpDuringTime(std::ostream& os = std::cout);

    static double second();
    static double millisecond();
};

Profiler::TimePoint Profiler::startTime;
Profiler::TimePoint Profiler::stopTime;
Profiler::DurationTime Profiler::duringTime;

void Profiler::start() { startTime = SteadyClock::now(); }

void Profiler::stop() {
    stopTime = SteadyClock::now();
    duringTime = std::chrono::duration_cast<DurationTime>(stopTime - startTime);
}

void Profiler::dumpDuringTime(std::ostream& os) {
    os << duringTime.count() * 1000 << " milliseconds" << std::endl;
}

double Profiler::second() { return duringTime.count(); }

double Profiler::millisecond() { return duringTime.count() * 1000; }

#endif  // PROFILER_HPP
