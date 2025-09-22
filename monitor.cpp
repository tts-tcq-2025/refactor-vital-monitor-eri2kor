#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

// Pure function: check if value is below/above range
BreachType checkLimit(float value, const Limit& limit) {
    return (value < limit.min) ? BreachType::LOW
         : (value > limit.max) ? BreachType::HIGH
         : BreachType::NORMAL;
}

// Pure function: convert enum to string
std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW:  return "LOW";
        case BreachType::HIGH: return "HIGH";
        default:               return "NORMAL";
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
    blinkPattern();
}

// Monitoring: 0 branching in vitalsOk
int vitalsOk(const std::vector<Vital>& vitals) {
    int allOk = 1; // assume OK

    for (const auto& v : vitals) {
        BreachType breach = checkLimit(v.value, v.limit);
        // Only side-effect (alert) depends on breach
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            allOk = 0;
        }
    }

    return allOk;
}
