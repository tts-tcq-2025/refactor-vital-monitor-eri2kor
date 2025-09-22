#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, AllVitalsNormal) {
  std::vector<Vital> vitals = {
    {"Temperature", 98.6, {95, 102}},
    {"Pulse Rate", 72, {60, 100}},
    {"Oxygen Saturation", 98, {90, 100}}
  };
  ASSERT_TRUE(vitalsOk(vitals));
}

TEST(Monitor, TemperatureTooHigh) {
  std::vector<Vital> vitals = {
    {"Temperature", 104, {95, 102}},
    {"Pulse Rate", 72, {60, 100}},
    {"Oxygen Saturation", 98, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}

TEST(Monitor, TemperatureTooLow) {
  std::vector<Vital> vitals = {
    {"Temperature", 94, {95, 102}},
    {"Pulse Rate", 72, {60, 100}},
    {"Oxygen Saturation", 98, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}

TEST(Monitor, PulseRateTooHigh) {
  std::vector<Vital> vitals = {
    {"Temperature", 98.6, {95, 102}},
    {"Pulse Rate", 120, {60, 100}},
    {"Oxygen Saturation", 98, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}

TEST(Monitor, PulseRateTooLow) {
  std::vector<Vital> vitals = {
    {"Temperature", 98.6, {95, 102}},
    {"Pulse Rate", 50, {60, 100}},
    {"Oxygen Saturation", 98, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}

TEST(Monitor, OxygenTooLow) {
  std::vector<Vital> vitals = {
    {"Temperature", 98.6, {95, 102}},
    {"Pulse Rate", 72, {60, 100}},
    {"Oxygen Saturation", 85, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}

TEST(Monitor, MultipleAbnormal) {
  std::vector<Vital> vitals = {
    {"Temperature", 104, {95, 102}},
    {"Pulse Rate", 120, {60, 100}},
    {"Oxygen Saturation", 85, {90, 100}}
  };
  ASSERT_FALSE(vitalsOk(vitals));
}
