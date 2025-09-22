#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace {

// Constants
constexpr float DEFAULT_WARNING_TOLERANCE = 0.015f;

// Blink alert helper
void blinkPattern(int cycles = 6, int delaySec = 1) {
    using namespace std::chrono_literals;
    for (int i = 0; i < cycles; ++i) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(delaySec));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(delaySec));
    }
}

} // namespace

// -------------------- Pure Functions --------------------
BreachType checkLimitWithWarning(float value, const Limit& limit, float tolerance) {
    const float tol = limit.max * tolerance;

    // Map value to BreachType without branching in main loop
    return (value < limit.min) ? BreachType::LOW :
           (value > limit.max) ? BreachType::HIGH :
           (value <= limit.min + tol) ? BreachType::WARNING_LOW :
           (value >= limit.max - tol) ? BreachType::WARNING_HIGH :
           BreachType::NORMAL;
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

void handleAlert(const Vital& v, BreachType breach) {
    std::cout << v.name << " is " << breachToString(breach) << "!\n";
    // Only LOW/HIGH triggers blink
    if (breach == BreachType::LOW || breach == BreachType::HIGH)
        blinkPattern();
}

// -------------------- Monitoring --------------------
int vitalsOk(const std::vector<Vital>& vitals) {
    // No branching: map each vital -> breach -> alert, combine results
    auto status = 1; // start assuming all OK
    for (const auto& v : vitals) {
        const auto breach = checkLimitWithWarning(v.value, v.limit, DEFAULT_WARNING_TOLERANCE);
        // Handle alert outside of monitoring logic
        if (breach != BreachType::NORMAL) handleAlert(v, breach);
        // Only LOW/HIGH counts as failure
        const int fail = static_cast<int>(breach == BreachType::LOW || breach == BreachType::HIGH);
        status &= (1 - fail); // update overall status
    }
    return status;
}
