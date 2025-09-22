#include "monitor.h"
#include <cassert>
#include <iostream>

void testVitals() {
    // Body temperature
    double upper = 102, lower = 95;
    double tolerance = calculateWarningTolerance(upper);

    assert(checkVital(98, lower, upper, tolerance) == VitalStatus::NORMAL);
    assert(checkVital(95 + tolerance - 0.01, lower, upper, tolerance) == VitalStatus::WARNING_LOW);
    assert(checkVital(102 - tolerance + 0.01, lower, upper, tolerance) == VitalStatus::WARNING_HIGH);
    assert(checkVital(94, lower, upper, tolerance) == VitalStatus::ALERT_LOW);
    assert(checkVital(103, lower, upper, tolerance) == VitalStatus::ALERT_HIGH);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    testVitals();
    return 0;
}
