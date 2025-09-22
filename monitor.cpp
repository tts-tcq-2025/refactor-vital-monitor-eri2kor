#include "monitor.h"
#include <iostream>
#include <algorithm> // for std::clamp

// Branchless status calculation
VitalStatus checkVital(double value, double lower, double upper, double warningTolerance) {
    double lowWarningThreshold = lower + warningTolerance;
    double highWarningThreshold = upper - warningTolerance;

    // Convert conditions to integers 0 or 1
    int isLowAlert    = static_cast<int>(value < lower);
    int isHighAlert   = static_cast<int>(value > upper);
    int isLowWarning  = static_cast<int>(value >= lower && value < lowWarningThreshold);
    int isHighWarning = static_cast<int>(value > highWarningThreshold && value <= upper);

    // Index: 0=ALERT_LOW, 1=WARNING_LOW, 2=NORMAL, 3=WARNING_HIGH, 4=ALERT_HIGH
    int index = 2 - isLowAlert + isHighAlert * 2 - isLowWarning + isHighWarning;

    index = std::clamp(index, 0, 4); // ensure in valid range

    return static_cast<VitalStatus>(index);
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
