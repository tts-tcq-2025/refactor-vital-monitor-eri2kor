#pragma once
#include <string>
#include <vector>

enum class BreachType { LOW, HIGH, NORMAL, WARNING_LOW, WARNING_HIGH };

struct Limit {
    float min{};
    float max{};
};

struct Vital {
    std::string name;
    float value{};
    Limit limit{};
};

// Pure functions
BreachType checkLimitWithWarning(float value, const Limit& limit, float tolerance = 0.015f);
std::string breachToString(BreachType breach);
void handleAlert(const Vital& v, BreachType breach);

// Monitoring function
int vitalsOk(const std::vector<Vital>& vitals);
