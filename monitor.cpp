#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

BreachType checkLimit(float value, const Limit& limit) {
    if (value < limit.min) return BreachType::LOW;
    if (value > limit.max) return BreachType::HIGH;
    return BreachType::NORMAL;
}

std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW: return "LOW";
        case BreachType::HIGH: return "HIGH";
        default: return "NORMAL";
    }
}

void blinkPattern(int cycles = 6, int delaySec = 1) {
    for (int i = 0; i < cycles; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(delaySec));
        cout << "\r *" << flush;
        sleep_for(seconds(delaySec));
    }
}

void alert(const Vital& v, BreachType breach) {
    cout << v.name << " is " << breachToString(breach) << "!\n";
    blinkPattern();
}

int vitalsOk(const std::vector<Vital>& vitals) {
    bool status = true;
    for (const auto& v : vitals) {
        BreachType breach = checkLimit(v.value, v.limit);
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            status = false;
        }
    }
    return status ? 1 : 0;
}
