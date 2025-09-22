#include "monitor.h"
#include <iostream>
#include <algorithm>

// Corrected logic: simplified and safe
VitalStatus checkVital(double value, double lower, double upper, double warningTolerance) {
    double lowWarning = lower + warningTolerance;
    double highWarning = upper - warningTolerance;

    if (value < lower) return VitalStatus::ALERT_LOW;
    if (value < lowWarning) return VitalStatus::WARNING_LOW;
    if (value <= highWarning) return VitalStatus::NORMAL;
    if (value <= upper) return VitalStatus::WARNING_HIGH;
    return VitalStatus::ALERT_HIGH;
}

double calculateWarningTolerance(double upper) {
    return upper * 0.015;
}

void displayStatus(const VitalSign& vital, VitalStatus status) {
    static const char* messages[] = {
        "ALERT: Below safe limit!",
        "Warning: Approaching low limit",
        "Normal",
        "Warning: Approaching high limit",
        "ALERT: Above safe limit!"
    };

    std::cout << vital.name << ": " << vital.value << " - "
              << messages[static_cast<int>(status)] << "\n";
}
