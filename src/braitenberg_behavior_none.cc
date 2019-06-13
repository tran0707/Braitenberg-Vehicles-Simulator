/**
* @file braitenberg_behavior_none.cc
*
* @copyright 2019 CSCI 3081 tran0707, All right reserved.
*/
#include "src/braitenberg_behavior_none.h"
#include "src/braitenberg_behaviors.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

Braitenberg_behavior_none::Braitenberg_behavior_none() {}
Braitenberg_behavior_none::~Braitenberg_behavior_none() {}

WheelVelocity Braitenberg_behavior_none::cal_wheel_velocity(
__unused const ArenaEntity *closest_entity, __unused double speed,
__unused std::vector<Pose> light_sensors) {
return WheelVelocity(0, 0);
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
