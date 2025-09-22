#pragma once
#include <string>
#include <vector>

// -------------------- Data Types --------------------
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

// -------------------- Pure Functions --------------------
// Check vital against limit and warning tolerance
BreachType checkLimitWithWarning(const float value, const Limit& limit, const float tolerance = 0.015f);

// Convert BreachType enum to string
std::string breachToString(const BreachType breach);

// -------------------- I/O Functions --------------------
// Handle alert printing and blinking
void handleAlert(const Vital& v, const BreachType breach);

// -------------------- Monitoring --------------------
// Returns 1 if all vitals are normal/warning, 0 if any LOW/HIGH
int vitalsOk(const std::vector<Vital>& vitals);
