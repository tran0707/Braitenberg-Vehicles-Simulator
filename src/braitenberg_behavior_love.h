/**
* @file braitenberg_behavior_love.h
*
* @copyright 2019 CSCI 3081 tran0707, All right reserved.
*/

#ifndef SRC_BRAITENBERG_BEHAVIOR_LOVE_H_
#define SRC_BRAITENBERG_BEHAVIOR_LOVE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include "src/behavior_enum.h"
#include "src/wheel_velocity.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/braitenberg_behaviors.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/**
* @brief A class for all braitenberg vehicle love behavior
* 
* This class uses to calculate the WheelVelocity of each BV based on
* love behavior
*/
class Braitenberg_behavior_love : public Braitenberg_behaviors {
 public:
/**
* @brief The constructor for BV love behavior.
*/
Braitenberg_behavior_love();

/**
* @brief The destructor for BV love behavior.
*/
virtual ~Braitenberg_behavior_love();

/**
* @brief Calculate the WheelVelocity of the closest_entity in case of love
*
* @param[in] closest_entity The closest food and light objects to this
* BV.
* @param[in] speed The default speed of BV
* @param[in] light_sensors An vector that stored two sensor reading left
* and right.
*/
WheelVelocity cal_wheel_velocity(const ArenaEntity *closest_entity,
double speed, std::vector<Pose> light_sensors) override;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_BRAITENBERG_BEHAVIOR_LOVE_H_
