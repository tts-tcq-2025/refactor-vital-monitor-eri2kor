#include "monitor.h"
#include <iostream>

VitalStatus checkVital(double value, double lower, double upper, double warningTolerance) {
    if (value < lower || value > upper) {
        return VitalStatus::ALERT;
    }
    if (value <= lower + warningTolerance || value >= upper - warningTolerance) {
        return VitalStatus::WARNING;
    }
    return VitalStatus::NORMAL;
}

double calculateWarningTolerance(double upper) {
    return upper * 0.015;
}

void displayStatus(const VitalSign& vital, VitalStatus status) {
    switch(status) {
        case VitalStatus::NORMAL:
            std::cout << vital.name << ": " << vital.value << " (Normal)\n";
            break;
        case VitalStatus::WARNING:
            if (vital.value < vital.lowerLimit + calculateWarningTolerance(vital.upperLimit)) {
                std::cout << vital.name << ": " << vital.value << " - Warning: Approaching low limit\n";
            } else {
                std::cout << vital.name << ": " << vital.value << " - Warning: Approaching high limit\n";
            }
            break;
        case VitalStatus::ALERT:
            if (vital.value < vital.lowerLimit) {
                std::cout << vital.name << ": " << vital.value << " - ALERT: Below safe limit!\n";
            } else {
                std::cout << vital.name << ": " << vital.value << " - ALERT: Above safe limit!\n";
            }
            break;
    }
}
