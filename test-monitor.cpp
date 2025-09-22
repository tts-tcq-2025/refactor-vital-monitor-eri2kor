#include <gtest/gtest.h>
#include "./monitor.h"

// Helper: create vitals vector
std::vector<Vital> makeVitals(float temp, float pulse, float spo2) {
    return {
        {"Temperature", temp, {95, 102}},
        {"Pulse Rate", pulse, {60, 100}},
        {"Oxygen Saturation", spo2, {90, 100}}
    };
}

// Test normal vitals
TEST(Monitor, AllVitalsNormal) {
    ASSERT_TRUE(vitalsOk(makeVitals(98.6, 72, 98)));
}

// Table-driven abnormal vitals
struct AbnormalCase { float temp, pulse, spo2; };
class MonitorAbnormalTest : public ::testing::TestWithParam<AbnormalCase> {};

TEST_P(MonitorAbnormalTest, DetectsOutOfRange) {
    auto c = GetParam();
    ASSERT_FALSE(vitalsOk(makeVitals(c.temp, c.pulse, c.spo2)));
}

// Instantiate all abnormal scenarios
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
