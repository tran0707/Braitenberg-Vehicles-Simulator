/**
* @file braitenberg_behaviors.h
*
* @copyright 2019 CSCI 3081 tran0707, All right reserved.
*/

#ifndef SRC_BRAITENBERG_BEHAVIORS_H_
#define SRC_BRAITENBERG_BEHAVIORS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "vector"
#include "src/behavior_enum.h"
#include "src/wheel_velocity.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/**
* @brief An abstract class for all braitenberg vehicle behaviors
* 
* This class uses to calculate the WheelVelocity of each BV based on
* the behaviors including explore, love, coward, and aggression.
*/
class Braitenberg_behaviors {
 public:
/**
* @brief Default constructor.
*/
Braitenberg_behaviors() {}

/**
* @brief Default destructor for BV behaviors.
*/
virtual ~Braitenberg_behaviors() {}

/**
* @brief Get reading of the left sensor on BV
*
* @param[in] entity This will be the ArenaEntity for light object.
* @param light_sensors The sensors of BV and Predator
*/
double get_sensor_reading_left(const ArenaEntity* entity,
std::vector<Pose> light_sensors) {
if (entity) {
return 1800.0/std::pow(
1.08, (entity->get_pose()-light_sensors[0]).Length());
}
return 0.0001;
}

/**
* @brief Get reading of the right sensor on BV
*
* @param[in] entity This will be the ArenaEntity for light object.
* @param light_sensors The sensors of BV and Predator
*/
double get_sensor_reading_right(const ArenaEntity* entity,
std::vector<Pose> light_sensors) {
if (entity) {
return 1800.0/std::pow(
1.08, (entity->get_pose()-light_sensors[1]).Length());
}
return 0.0001;
}

/**
* @brief Calculate the WheelVelocity of the closest_entity
*
* @param[in] closest_entity The closest food and light objects to this
* BV.
* @param[in] speed The default speed of BV
* @param[in] light_sensors An vector that stored two sensor reading left
* and right.
*/
virtual WheelVelocity cal_wheel_velocity(const ArenaEntity *closest_entity,
double speed, std::vector<Pose> light_sensors) = 0;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_BRAITENBERG_BEHAVIORS_H_
