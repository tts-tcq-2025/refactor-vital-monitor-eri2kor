#include "monitor.h"
#include <iostream>

double calculateWarningTolerance(double upper) {
    return upper * 0.015; // 1.5% of upper limit
}

VitalStatus checkVital(double value, double lower, double upper, double warningTolerance) {
    if (value < lower) return VitalStatus::ALERT_LOW;
    if (value < lower + warningTolerance) return VitalStatus::WARNING_LOW;
    if (value > upper) return VitalStatus::ALERT_HIGH;
    if (value > upper - warningTolerance) return VitalStatus::WARNING_HIGH;
    return VitalStatus::NORMAL;
}

void displayStatus(const VitalSign& vital, VitalStatus status) {
    switch (status) {
        case VitalStatus::NORMAL:
            std::cout << vital.name << ": " << vital.value << " - Normal\n";
            break;
        case VitalStatus::WARNING_LOW:
            std::cout << vital.name << ": " << vital.value << " - Warning: Approaching low limit\n";
            break;
        case VitalStatus::WARNING_HIGH:
            std::cout << vital.name << ": " << vital.value << " - Warning: Approaching high limit\n";
            break;
        case VitalStatus::ALERT_LOW:
            std::cout << vital.name << ": " << vital.value << " - ALERT: Below safe limit!\n";
            break;
        case VitalStatus::ALERT_HIGH:
            std::cout << vital.name << ": " << vital.value << " - ALERT: Above safe limit!\n";
            break;
    }
}
