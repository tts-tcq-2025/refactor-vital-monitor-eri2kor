#ifndef MONITOR_H
#define MONITOR_H

#include <string>

struct VitalSign {
    std::string name;
    double value;
    double lowerLimit;
    double upperLimit;
};

enum class VitalStatus { ALERT_LOW, WARNING_LOW, NORMAL, WARNING_HIGH, ALERT_HIGH };

// Pure functions
VitalStatus checkVital(double value, double lower, double upper, double warningTolerance);
double calculateWarningTolerance(double upper);

// I/O functions
void displayStatus(const VitalSign& vital, VitalStatus status);

#endif // MONITOR_H
