/**
 * @file braitenberg_aggression_unittest.cc
 *
 * @copyright 2019 tran0707 , All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <vector>
#include "src/light.h"
#include "src/braitenberg_behavior_aggression.h"
#include "src/braitenberg_behaviors.h"
#include "src/wheel_velocity.h"

NAMESPACE_BEGIN(csci3081);
/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BV_Aggression_Test: public ::testing::Test {
 protected:
virtual void SetUp() {
// Test case 1
light_entity_1 = new Light();
light_sensor_1.push_back(Pose(50, 50));
light_sensor_1.push_back(Pose(10, 10));

// Test case 2
light_entity_2 = new Light();
light_sensor_2.push_back(Pose(200, 100));
light_sensor_2.push_back(Pose(300, 100));
}
virtual void TearDown() {
delete light_entity_1;
delete light_entity_2;
}
// Test case 1
Light * light_entity_1;
std::vector<Pose>light_sensor_1;
WheelVelocity velocity_expected_1;

// Test case 2
Light * light_entity_2;
std::vector<Pose>light_sensor_2;
WheelVelocity velocity_expected_2;

// Declaration
Braitenberg_behavior_aggression bva;
double speed = 100.0;
};
/****************************************************
 * Test Cases
 ***************************************************/
TEST_F(BV_Aggression_Test, WheelVolocityAggression) {
// Case 1
WheelVelocity wv_aggression_1 = bva.cal_wheel_velocity(
light_entity_1, speed, light_sensor_1);

// Case 2
WheelVelocity wv_aggression_2 = bva.cal_wheel_velocity(
light_entity_2, speed, light_sensor_2);

// print answers
// std::cout << "left1: " << wv_aggression_1.left << std::endl;
// std::cout << "right1: "<< wv_aggression_1.right << std::endl;
// std::cout << "left2: " << wv_aggression_2.left << std::endl;
// std::cout << "right2: "<< wv_aggression_2.right << std::endl;

velocity_expected_1 = WheelVelocity(1.88057e-06, 0.000146226);
velocity_expected_2 = WheelVelocity(0.0337629, 0.818271);

bool aggression_behav_bool_1 = (wv_aggression_1 == velocity_expected_1);
bool aggression_behav_bool_2 = (wv_aggression_2 == velocity_expected_2);


EXPECT_TRUE(aggression_behav_bool_1)
<< "FAIL1: Wrong Aggression Behavior in term of WheelVelocity";
EXPECT_TRUE(aggression_behav_bool_2)
<< "FAIL2: Wrong Aggression Behavior in term of WheelVelocity";
}
NAMESPACE_END(csci3081);
