#pragma once
#include <string>
#include <vector>

enum class BreachType { LOW, HIGH, NORMAL };

struct Limit {
    float min;
    float max;
};

struct Vital {
    std::string name;
    float value;
    Limit limit;
};

// Pure functions
BreachType checkLimit(float value, const Limit& limit);
std::string breachToString(BreachType breach);

// Monitoring function
int vitalsOk(const std::vector<Vital>& vitals);
