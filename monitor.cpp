#include "monitor.h"
#include <iostream>

// Zero complexity logic using arithmetic comparison
VitalStatus checkVital(double value, double lower, double upper, double warningTolerance) {
    double lowWarningThreshold = lower + warningTolerance;
    double highWarningThreshold = upper - warningTolerance;

    // Map value to status without branching
    VitalStatus statuses[] = {
        VitalStatus::ALERT_LOW,     // value < lower
        VitalStatus::WARNING_LOW,   // lower <= value < lowWarningThreshold
        VitalStatus::NORMAL,        // lowWarningThreshold <= value <= highWarningThreshold
        VitalStatus::WARNING_HIGH,  // highWarningThreshold < value <= upper
        VitalStatus::ALERT_HIGH     // value > upper
    };

    // Compute index (0-4) without branching
    int index = 2 // assume NORMAL
        - (value < lower) 
        + (value > upper) * 2
        - (value >= lower && value < lowWarningThreshold)
        + (value > highWarningThreshold && value <= upper);

    // clamp index to [0,4]
    if (index < 0) index = 0;
    if (index > 4) index = 4;

    return statuses[index];
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

    std::cout << vital.name << ": " << vital.value << " - " << messages[static_cast<int>(status)] << "\n";
}
