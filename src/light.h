/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <ctime>

#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile light within the Arena.
 *
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light " + std::to_string(get_id());
  }

  /**
   * @brief Update the lights's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Handle any collisions with the light
   */
  void HandleCollision(EntityType ent_type, ArenaEntity * object = NULL)
    override;

  //! count ID
  static int count;

 private:
  MotionBehaviorDifferential motion_behavior_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
