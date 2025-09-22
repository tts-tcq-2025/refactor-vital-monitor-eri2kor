#include "monitor.h"
#include <cassert>
#include <iostream>

void testVitals() {
    // Body Temperature
    double upperTemp = 102, lowerTemp = 95;
    double toleranceTemp = calculateWarningTolerance(upperTemp);

    assert(checkVital(98, lowerTemp, upperTemp, toleranceTemp) == VitalStatus::NORMAL);
    assert(checkVital(95 + toleranceTemp - 0.01, lowerTemp, upperTemp, toleranceTemp) == VitalStatus::WARNING_LOW);
    assert(checkVital(102 - toleranceTemp + 0.01, lowerTemp, upperTemp, toleranceTemp) == VitalStatus::WARNING_HIGH);
    assert(checkVital(94, lowerTemp, upperTemp, toleranceTemp) == VitalStatus::ALERT_LOW);
    assert(checkVital(103, lowerTemp, upperTemp, toleranceTemp) == VitalStatus::ALERT_HIGH);

    // Pulse Rate
    double upperPulse = 100, lowerPulse = 60;
    double tolerancePulse = calculateWarningTolerance(upperPulse);

    assert(checkVital(80, lowerPulse, upperPulse, tolerancePulse) == VitalStatus::NORMAL);
    assert(checkVital(60 + tolerancePulse - 0.01, lowerPulse, upperPulse, tolerancePulse) == VitalStatus::WARNING_LOW);
    assert(checkVital(100 - tolerancePulse + 0.01, lowerPulse, upperPulse, tolerancePulse) == VitalStatus::WARNING_HIGH);
    assert(checkVital(59, lowerPulse, upperPulse, tolerancePulse) == VitalStatus::ALERT_LOW);
    assert(checkVital(101, lowerPulse, upperPulse, tolerancePulse) == VitalStatus::ALERT_HIGH);

    // SpO2
    double upperSpO2 = 100, lowerSpO2 = 90;
    double toleranceSpO2 = calculateWarningTolerance(upperSpO2);

    assert(checkVital(95, lowerSpO2, upperSpO2, toleranceSpO2) == VitalStatus::NORMAL);
    assert(checkVital(90 + toleranceSpO2 - 0.01, lowerSpO2, upperSpO2, toleranceSpO2) == VitalStatus::WARNING_LOW);
    assert(checkVital(100 - toleranceSpO2 + 0.01, lowerSpO2, upperSpO2, toleranceSpO2) == VitalStatus::WARNING_HIGH);
    assert(checkVital(89, lowerSpO2, upperSpO2, toleranceSpO2) == VitalStatus::ALERT_LOW);
    assert(checkVital(101, lowerSpO2, upperSpO2, toleranceSpO2) == VitalStatus::ALERT_HIGH);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    testVitals();
    return 0;
}
