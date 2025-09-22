#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

// Pure function: check if value is below/above range
BreachType checkLimit(float value, const Limit& limit) {
    return (value < limit.min) ? BreachType::LOW
         : (value > limit.max) ? BreachType::HIGH
         : BreachType::NORMAL;
}

// New: check with warning ranges
BreachType checkLimitWithWarning(float value, const Limit& limit, float tolerance) {
    float warnLow  = limit.min;
    float warnHigh = limit.max;
    float tol      = limit.max * tolerance; // 1.5% of upper limit

    if (value < warnLow) return BreachType::LOW;
    if (value > warnHigh) return BreachType::HIGH;
    if (value >= warnLow && value <= warnLow + tol) return BreachType::WARNING_LOW;
    if (value >= warnHigh - tol && value <= warnHigh) return BreachType::WARNING_HIGH;

    return BreachType::NORMAL;
}

// Pure function: convert enum to string
std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW: return "LOW";
        case BreachType::HIGH: return "HIGH";
        case BreachType::WARNING_LOW: return "WARNING_LOW";
        case BreachType::WARNING_HIGH: return "WARNING_HIGH";
        default: return "NORMAL";
    }
}

// Reusable alert blinking
static void blinkPattern(int cycles = 6, int delaySec = 1) {
    using namespace std::chrono;
    using namespace std::this_thread;
    for (int i = 0; i < cycles; i++) {
        std::cout << "\r* " << std::flush;
        sleep_for(seconds(delaySec));
        std::cout << "\r *" << std::flush;
        sleep_for(seconds(delaySec));
    }
}

// Reusable alert printing
static void alert(const Vital& v, BreachType breach) {
    std::cout << v.name << " is " << breachToString(breach) << "!\n";
    if (breach == BreachType::LOW || breach == BreachType::HIGH)
        blinkPattern();
}

// Monitoring: 0 branching in vitalsOk
int vitalsOk(const std::vector<Vital>& vitals) {
    int allOk = 1; // assume OK

    for (const auto& v : vitals) {
        BreachType breach = checkLimitWithWarning(v.value, v.limit);
        // Only side-effect (alert) depends on breach
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            if (breach == BreachType::LOW || breach == BreachType::HIGH)
                allOk = 0;
        }
    }

    return allOk;
}
