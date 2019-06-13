/**
* @file braitenberg_behavior_explore.cc
*
* @copyright 2019 CSCI 3081 tran0707, All right reserved.
*/
#include "src/braitenberg_behavior_explore.h"
#include "src/braitenberg_behaviors.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

Braitenberg_behavior_explore::Braitenberg_behavior_explore() {}
Braitenberg_behavior_explore::~Braitenberg_behavior_explore() {}

WheelVelocity Braitenberg_behavior_explore::cal_wheel_velocity(
const ArenaEntity *closest_entity, double speed,
std::vector<Pose> light_sensors) {
WheelVelocity return_velocity_explore = WheelVelocity(0, 0);
return_velocity_explore = WheelVelocity(
    1.0/get_sensor_reading_right(closest_entity, light_sensors),
    1.0/get_sensor_reading_left(closest_entity, light_sensors), speed);
return return_velocity_explore;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
