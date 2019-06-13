/**
 * @file predator.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PREDATOR_H_
#define SRC_PREDATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/braitenberg_behaviors.h"
#include "src/braitenberg_behavior_love.h"
#include "src/braitenberg_behavior_explore.h"
#include "src/braitenberg_behavior_coward.h"
#include "src/braitenberg_behavior_aggression.h"
#include "src/braitenberg_behavior_none.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An Entity class represent for A Braitenberg Vehicle with the ability
 * of eating/killing the other Braitenberg Vehicle. 
 */
class Predator : public ArenaMobileEntity {
 public:
  Predator();
  Predator(const Predator &rhs) = delete;
  Predator operator=(const Predator &rhs) = delete;

  /**
   * @brief Update the Predaroe's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */ 
  void TimestepUpdate(unsigned int dt) override;

  /**
  * @brief Update Function for Predator
  */
  void Update() override;

  /**
   * @brief Change the movement state of the Vehicle when collision occur.
   *
   * @param ent_type The Entitytype of collision Entity
   * @param object The object that collision with
   */
  void HandleCollision(EntityType ent_type,
  ArenaEntity * object = NULL) override;

  /**
  * @brief Sense the entity arround including food, light , and BV
  *
  * @param[in] entity The entity need to sense
  */
  void SenseEntity(const ArenaEntity& entity);

  /**
  * @brief Return name of Braitenberg Vehicle with ID
  */
  std::string get_name() const override;

  /**
   * @brief Getter function to get light_sensors const
   */ 
  std::vector<Pose> get_light_sensors_const() const;

  /**
   * @brief Getter function to get light_sensors
   */
  std::vector<Pose> get_light_sensors();

  /**
  * @brief Update the position x and y of light_sensor_ left and right
  */
  void UpdateLightSensors();

  /**
  * @brief Load json file into Predator
  *
  * @param entity_config The config from Json file
  */
  void LoadFromObject(json_object* entity_config) override;

  //! count ID
  static int count;

  //! number of collision
  int collision_count = 0;
  //! flag that check if collision occured
  bool collision_flag = false;

  /**
  * @brief A simgle getter function for light behavior
  */
  Behavior get_light_behavior() {return kCoward; }

  /**
  * @brief A simgle getter function for food behavior
  */
  Behavior get_food_behavior() {return kNone; }

  /**
  * @brief A simgle getter function for BV behavior
  */ 
  Behavior get_bv_behavior() {return kAggressive; }

  /**
  * @brief A simgle getter function for Predator behavior
  */ 
  Behavior get_predator_behavior() {return kNone; }

  /**
  * @brief A setter function that set the Behavior type to the light behavior
  * alse create new Predator class
  */
  void set_light_behavior() {
  light_behavior_ = new Braitenberg_behavior_coward();
  }

  /**
  * @brief A setter function that set the Behavior type to the food behavior
  * alse create new Predator class
  */
  void set_food_behavior() {
  food_behavior_ = new Braitenberg_behavior_none();
  }

  /**
  * @brief A setter function that set the Behavior type to the bv behavior
  * alse create new Predator class
  */
  void set_bv_behavior() {
  bv_behavior_ = new Braitenberg_behavior_aggression();
  }

 /**
  * @brief A setter function that set the Behavior type to the Predator behavior
  * alse create new Predator class
  */
  void set_predator_behavior() {
    predator_behavior_ = new Braitenberg_behavior_none();
  }

  bool is_collision_with_bv() override;

 private:
  std::vector<Pose> light_sensors_;
  MotionBehaviorDifferential * motion_behavior_{nullptr};
  WheelVelocity wheel_velocity_;
  // for all BV behaviors
  Braitenberg_behaviors* light_behavior_;
  Braitenberg_behaviors* food_behavior_;
  Braitenberg_behaviors* bv_behavior_;
  Braitenberg_behaviors* predator_behavior_;

  const ArenaEntity* closest_light_entity_;
  const ArenaEntity* closest_food_entity_;
  const ArenaEntity* closest_bv_entity_;
  const ArenaEntity* closest_predator_entity_;
  double defaultSpeed_;
  double numBehaviors_;
  bool collision_with_bv;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_PREDATOR_H_
