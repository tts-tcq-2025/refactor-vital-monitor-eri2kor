#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace {

// -------------------- Constants --------------------
constexpr float DEFAULT_WARNING_TOLERANCE = 0.015f;

// -------------------- Alert Helpers --------------------
void blinkPattern(int cycles = 6, int delaySec = 1) {
    using namespace std::chrono_literals;
    for (int i = 0; i < cycles; ++i) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(delaySec));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(delaySec));
    }
}

void alert(const Vital& v, BreachType breach) {
    std::cout << v.name << " is " << breachToString(breach) << "!\n";
    if (breach == BreachType::LOW || breach == BreachType::HIGH) {
        blinkPattern();
    }
}

} // namespace

// -------------------- Pure Functions --------------------
BreachType checkLimit(float value, const Limit& limit) {
    if (value < limit.min) return BreachType::LOW;
    if (value > limit.max) return BreachType::HIGH;
    return BreachType::NORMAL;
}

BreachType checkLimitWithWarning(float value, const Limit& limit, float tolerance) {
    const float tol = limit.max * tolerance;

    if (value < limit.min) return BreachType::LOW;
    if (value > limit.max) return BreachType::HIGH;
    if (value <= limit.min + tol) return BreachType::WARNING_LOW;
    if (value >= limit.max - tol) return BreachType::WARNING_HIGH;
    return BreachType::NORMAL;
}

std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW: return "LOW";
        case BreachType::HIGH: return "HIGH";
        case BreachType::WARNING_LOW: return "WARNING_LOW";
        case BreachType::WARNING_HIGH: return "WARNING_HIGH";
        default: return "NORMAL";
    }
}

// -------------------- Monitoring --------------------
int vitalsOk(const std::vector<Vital>& vitals) {
    int allOk = 1;
    for (const auto& v : vitals) {
        const auto breach = checkLimitWithWarning(v.value, v.limit, DEFAULT_WARNING_TOLERANCE);
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            allOk &= !(breach == BreachType::LOW || breach == BreachType::HIGH) ? 1 : 0;
        }
    }
    return allOk;
}
