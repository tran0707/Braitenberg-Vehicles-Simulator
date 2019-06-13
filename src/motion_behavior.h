/**
 * @file motion_behavior.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_BEHAVIOR_H_
#define SRC_MOTION_BEHAVIOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/wheel_velocity.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class managing an ArenaMobileEntity's position.
 *
 * Update the position foodd on the current speed and position. This
 * is simple, but the framework allows for more sophisticated models of
 * motion in which each wheel has different speeds.
 */
class MotionBehavior {
 public:
  /**
   * @brief Default constructor.
   */
  explicit MotionBehavior(ArenaMobileEntity * ent);

  virtual ~MotionBehavior() = default;

  //! Copy constructor
  MotionBehavior(const MotionBehavior& other) = default;
  //! Copy constructor
  MotionBehavior& operator=(const MotionBehavior& other) = default;

  /**
   * @brief Update the position (and possibly orientation) for an
   * ArenaMobileEntity, foodd on its current position and velocity.
   *
   * @param[in] dt # of timesteps elapsed since the last update.
   * @param[in] vel WheelVelocity stored within the motion handler
   */
  virtual void UpdatePose(double dt, WheelVelocity vel = WheelVelocity());

  /**
  * @brief Getter of entity in which this class was created.
  */
  ArenaMobileEntity * get_entity() { return entity_; }

 protected:
  //! The entity in which this behavior exists
  ArenaMobileEntity * entity_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_BEHAVIOR_H_
