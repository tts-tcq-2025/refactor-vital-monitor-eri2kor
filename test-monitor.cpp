#include "monitor.h"
#include <cassert>
#include <iostream>

void testVitals() {
    // Body temperature tests
    double tempUpper = 102, tempLower = 95;
    double tempTolerance = calculateWarningTolerance(tempUpper);

    // Normal
    assert(checkVital(98, tempLower, tempUpper, tempTolerance) == VitalStatus::NORMAL);

    // Warning low
    assert(checkVital(95 + tempTolerance, tempLower, tempUpper, tempTolerance) == VitalStatus::WARNING);

    // Warning high
    assert(checkVital(102 - tempTolerance, tempLower, tempUpper, tempTolerance) == VitalStatus::WARNING);

    // Alert low
    assert(checkVital(94, tempLower, tempUpper, tempTolerance) == VitalStatus::ALERT);

    // Alert high
    assert(checkVital(103, tempLower, tempUpper, tempTolerance) == VitalStatus::ALERT);

    // Pulse rate tests
    double pulseUpper = 100, pulseLower = 60;
    double pulseTolerance = calculateWarningTolerance(pulseUpper);

    assert(checkVital(80, pulseLower, pulseUpper, pulseTolerance) == VitalStatus::NORMAL);
    assert(checkVital(60 + pulseTolerance, pulseLower, pulseUpper, pulseTolerance) == VitalStatus::WARNING);
    assert(checkVital(100 - pulseTolerance, pulseLower, pulseUpper, pulseTolerance) == VitalStatus::WARNING);
    assert(checkVital(59, pulseLower, pulseUpper, pulseTolerance) == VitalStatus::ALERT);
    assert(checkVital(101, pulseLower, pulseUpper, pulseTolerance) == VitalStatus::ALERT);

    // SpO2 tests
    double spo2Upper = 100, spo2Lower = 90;
    double spo2Tolerance = calculateWarningTolerance(spo2Upper);

    assert(checkVital(95, spo2Lower, spo2Upper, spo2Tolerance) == VitalStatus::NORMAL);
    assert(checkVital(90 + spo2Tolerance, spo2Lower, spo2Upper, spo2Tolerance) == VitalStatus::WARNING);
    assert(checkVital(100 - spo2Tolerance, spo2Lower, spo2Upper, spo2Tolerance) == VitalStatus::WARNING);
    assert(checkVital(89, spo2Lower, spo2Upper, spo2Tolerance) == VitalStatus::ALERT);
    assert(checkVital(101, spo2Lower, spo2Upper, spo2Tolerance) == VitalStatus::ALERT);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    testVitals();
    return 0;
}
