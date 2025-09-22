#include "monitor.h"
#include <cassert>
#include <iostream>

void runTests() {
    // Body Temperature
    double lowerTemp = 95, upperTemp = 102;
    double tolTemp = calculateWarningTolerance(upperTemp);

    assert(checkVital(97, lowerTemp, upperTemp, tolTemp) == VitalStatus::NORMAL);
    assert(checkVital(95.5, lowerTemp, upperTemp, tolTemp) == VitalStatus::WARNING_LOW);
    assert(checkVital(101, lowerTemp, upperTemp, tolTemp) == VitalStatus::WARNING_HIGH);
    assert(checkVital(94, lowerTemp, upperTemp, tolTemp) == VitalStatus::ALERT_LOW);
    assert(checkVital(103, lowerTemp, upperTemp, tolTemp) == VitalStatus::ALERT_HIGH);

    // Pulse Rate
    double lowerPulse = 60, upperPulse = 100;
    double tolPulse = calculateWarningTolerance(upperPulse);

    assert(checkVital(80, lowerPulse, upperPulse, tolPulse) == VitalStatus::NORMAL);
    assert(checkVital(61, lowerPulse, upperPulse, tolPulse) == VitalStatus::WARNING_LOW);
    assert(checkVital(99, lowerPulse, upperPulse, tolPulse) == VitalStatus::WARNING_HIGH);
    assert(checkVital(59, lowerPulse, upperPulse, tolPulse) == VitalStatus::ALERT_LOW);
    assert(checkVital(101, lowerPulse, upperPulse, tolPulse) == VitalStatus::ALERT_HIGH);

    // SpO2
    double lowerSpO2 = 90, upperSpO2 = 100;
    double tolSpO2 = calculateWarningTolerance(upperSpO2);

    assert(checkVital(95, lowerSpO2, upperSpO2, tolSpO2) == VitalStatus::NORMAL);
    assert(checkVital(90.5, lowerSpO2, upperSpO2, tolSpO2) == VitalStatus::WARNING_LOW);
    assert(checkVital(99, lowerSpO2, upperSpO2, tolSpO2) == VitalStatus::WARNING_HIGH);
    assert(checkVital(89, lowerSpO2, upperSpO2, tolSpO2) == VitalStatus::ALERT_LOW);
    assert(checkVital(101, lowerSpO2, upperSpO2, tolSpO2) == VitalStatus::ALERT_HIGH);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    runTests();
    return 0;
}
