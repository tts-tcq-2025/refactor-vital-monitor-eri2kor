#include <gtest/gtest.h>
#include "./monitor.h"

// -------------------- Helpers --------------------
std::vector<Vital> makeVitals(float temp, float pulse, float spo2) {
    return {
        {"Temperature", temp, {95, 102}},
        {"Pulse Rate", pulse, {60, 100}},
        {"Oxygen Saturation", spo2, {90, 100}}
    };
}

// -------------------- Normal Vitals --------------------
TEST(Monitor, AllVitalsNormal) {
    ASSERT_TRUE(vitalsOk(makeVitals(98.6, 72, 98)));
}

// -------------------- Abnormal Vitals (Alarms) --------------------
struct AbnormalCase { float temp, pulse, spo2; };
class MonitorAbnormalTest : public ::testing::TestWithParam<AbnormalCase> {};

TEST_P(MonitorAbnormalTest, DetectsOutOfRange) {
    auto c = GetParam();
    ASSERT_FALSE(vitalsOk(makeVitals(c.temp, c.pulse, c.spo2)));
}

INSTANTIATE_TEST_SUITE_P(
    AbnormalCases, MonitorAbnormalTest,
    ::testing::Values(
        AbnormalCase{104, 72, 98},   // High temp
        AbnormalCase{94, 72, 98},    // Low temp
        AbnormalCase{98.6, 120, 98}, // High pulse
        AbnormalCase{98.6, 50, 98},  // Low pulse
        AbnormalCase{98.6, 72, 85},  // Low spo2
        AbnormalCase{104, 120, 85}   // Multiple abnormal
    )
);

// -------------------- Warning Vitals --------------------
struct WarningCase { float temp, pulse, spo2; };
class MonitorWarningTest : public ::testing::TestWithParam<WarningCase> {};

TEST_P(MonitorWarningTest, DetectsWarningRanges) {
    auto c = GetParam();
    // Warnings should NOT fail vitalsOk
    ASSERT_TRUE(vitalsOk(makeVitals(c.temp, c.pulse, c.spo2)));
}

INSTANTIATE_TEST_SUITE_P(
    WarningCases, MonitorWarningTest,
    ::testing::Values(
        WarningCase{95 + 0.5, 72, 98},    // Temp near lower warning
        WarningCase{102 - 1.5, 72, 98},   // Temp near upper warning
        WarningCase{98.6, 60 + 1, 98},    // Pulse near lower warning
        WarningCase{98.6, 100 - 1, 98},   // Pulse near upper warning
        WarningCase{98.6, 72, 90 + 0.5},  // SPO2 near lower warning
        WarningCase{98.6, 72, 100}        // SPO2 near upper warning
    )
);
