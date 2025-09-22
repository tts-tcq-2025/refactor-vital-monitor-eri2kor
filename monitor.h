#ifndef MONITOR_H
#define MONITOR_H

#include <string>

struct VitalSign {
    std::string name;
    double value;
    double lowerLimit;
    double upperLimit;
};

enum class VitalStatus { NORMAL, WARNING_LOW, WARNING_HIGH, ALERT_LOW, ALERT_HIGH };

// Pure functions
double calculateWarningTolerance(double upper);
VitalStatus checkVital(double value, double lower, double upper, double warningTolerance);

// I/O function
void displayStatus(const VitalSign& vital, VitalStatus status);

#endif // MONITOR_H
