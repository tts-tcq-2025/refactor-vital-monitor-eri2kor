#include "monitor.h"
#include <iostream>

int main() {
    // Sample adult vitals
    VitalSign vitals[] = {
        {"Body Temperature (°F)", 101.0, 95.0, 102.0},
        {"Pulse Rate (bpm)", 98, 60, 100},
        {"SpO2 (%)", 93, 90, 100}
    };

    for (const auto& vital : vitals) {
        double tolerance = calculateWarningTolerance(vital.upperLimit);
        VitalStatus status = checkVital(vital.value, vital.lowerLimit, vital.upperLimit, tolerance);
        displayStatus(vital, status);
    }

    return 0;
}
