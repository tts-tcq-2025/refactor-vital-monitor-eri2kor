#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

// -------------------- Pure Functions --------------------

// Basic limit check
BreachType checkLimit(float value, const Limit& limit) {
    return (value < limit.min) ? BreachType::LOW
         : (value > limit.max) ? BreachType::HIGH
         : BreachType::NORMAL;
}

// Limit check with warning thresholds (1.5% by default)
BreachType checkLimitWithWarning(float value, const Limit& limit, float tolerance) {
    float tol = limit.max * tolerance;
    if (value < limit.min) return BreachType::LOW;
    if (value > limit.max) return BreachType::HIGH;
    if (value >= limit.min && value <= limit.min + tol) return BreachType::WARNING_LOW;
    if (value >= limit.max - tol && value <= limit.max) return BreachType::WARNING_HIGH;
    return BreachType::NORMAL;
}

// Convert enum to string
std::string breachToString(BreachType breach) {
    switch (breach) {
        case BreachType::LOW: return "LOW";
        case BreachType::HIGH: return "HIGH";
        case BreachType::WARNING_LOW: return "WARNING_LOW";
        case BreachType::WARNING_HIGH: return "WARNING_HIGH";
        default: return "NORMAL";
    }
}

// -------------------- Alert Helpers --------------------

// Simple blinking alert for alarms
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

// Print alerts and warnings
static void alert(const Vital& v, BreachType breach) {
    std::cout << v.name << " is " << breachToString(breach) << "!\n";
    if (breach == BreachType::LOW || breach == BreachType::HIGH)
        blinkPattern();
}

// -------------------- Monitoring --------------------

int vitalsOk(const std::vector<Vital>& vitals) {
    int allOk = 1;
    for (const auto& v : vitals) {
        BreachType breach = checkLimitWithWarning(v.value, v.limit);
        if (breach != BreachType::NORMAL) {
            alert(v, breach);
            if (breach == BreachType::LOW || breach == BreachType::HIGH)
                allOk = 0;
        }
    }
    return allOk;
}
