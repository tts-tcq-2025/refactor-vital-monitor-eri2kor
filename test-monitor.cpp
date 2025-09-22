#include <gtest/gtest.h>
#include "monitor.h"

// -------------------- Helpers --------------------
std::vector<Vital> makeVitals(float temp, float pulse, float spo2) {
    return {
        {"Temperature", temp, {95.0f, 102.0f}},
        {"Pulse Rate", pulse, {60.0f, 100.0f}},
        {"Oxygen Saturation", spo2, {90.0f, 100.0f}}
    };
}

// -------------------- Normal Vitals --------------------
TEST(Monitor, AllVitalsNormal) {
    ASSERT_TRUE(vitalsOk(makeVitals(98.6f, 72.0f, 98.0f)));
}

// -------------------- Abnormal Vitals (Alarms) --------------------
struct AbnormalCase { float temp, pulse, spo2; };
class MonitorAbnormalTest : public ::testing::TestWithParam<AbnormalCase> {};

TEST_P(MonitorAbnormalTest, DetectsOutOfRange) {
    const auto c = GetParam();
    ASSERT_FALSE(vitalsOk(makeVitals(c.temp, c.pulse, c.spo2)));
}

INSTANTIATE_TEST_SUITE_P(
    AbnormalCases, MonitorAbnormalTest,
    ::testing::Values(
        AbnormalCase{104.0f, 72.0f, 98.0f},
        AbnormalCase{94.0f, 72.0f, 98.0f},
        AbnormalCase{98.6f, 120.0f, 98.0f},
        AbnormalCase{98.6f, 50.0f, 98.0f},
        AbnormalCase{98.6f, 72.0f, 85.0f},
        AbnormalCase{104.0f, 120.0f, 85.0f}
    )
);

// -------------------- Warning Vitals --------------------
struct WarningCase { float temp, pulse, spo2; };
class MonitorWarningTest : public ::testing::TestWithParam<WarningCase> {};

TEST_P(MonitorWarningTest, DetectsWarningRanges) {
    const auto c = GetParam();
    ASSERT_TRUE(vitalsOk(makeVitals(c.temp, c.pulse, c.spo2)));
}

INSTANTIATE_TEST_SUITE_P(
    WarningCases, MonitorWarningTest,
    ::testing::Values(
        WarningCase{95.5f, 72.0f, 98.0f},
        WarningCase{100.5f, 72.0f, 98.0f},
        WarningCase{98.6f, 61.0f, 98.0f},
        WarningCase{98.6f, 99.0f, 98.0f},
        WarningCase{98.6f, 72.0f, 90.5f},
        WarningCase{98.6f, 72.0f, 100.0f}
    )
);
