#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

BreachType checkLimit(float value, const Limit& limit) {
    if (value < limit.min) return BreachType::LOW;
    if (value > limit.max) return BreachType::HIGH;
    return BreachType::NORMAL;
}

std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW:  return "LOW";
        case BreachType::HIGH: return "HIGH";
        default:               return "NORMAL";
    }
}

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

static void alert(const Vital& v, BreachType breach) {
    std::cout << v.name << " is " << breachToString(breach) << "!\n";
    blinkPattern();
}

int vitalsOk(const std::vector<Vital>& vitals) {
    bool allOk = true;
    for (const auto& v : vitals) {
        BreachType breach = checkLimit(v.value, v.limit);
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            allOk = false;
        }
    }
    return allOk ? 1 : 0;
}
