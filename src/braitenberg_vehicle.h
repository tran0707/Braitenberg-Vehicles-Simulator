/**
 * @file braitenberg_vehicle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BRAITENBERG_VEHICLE_H_
#define SRC_BRAITENBERG_VEHICLE_H_

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
#include "src/observer.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
class Observer;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Entity class to represent a Braitenberg Vehicle
 * 
 * A braitenberg vehicle is a simple machine that is used to show how simple
 * concepts (in this case wiring) can give way to complex looking behavior. In
 * this simulation, Braitenberg vehicles contain sensors, which can be hooked
 * up in four different ways, and thus they can exhibit four different behaviors
 */
class BraitenbergVehicle : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  BraitenbergVehicle();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  BraitenbergVehicle(const BraitenbergVehicle & rhs) = delete;

  BraitenbergVehicle operator=(const BraitenbergVehicle & rhs) = delete;

  /**
   * @brief Update the BraitenbergVehicle's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

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
  * @brief Load json file into BV
  *
  * @param entity_config The config from Json file
  */
  void LoadFromObject(json_object* entity_config) override;

  //! couting ID
  static int count;
// Add collision_count and collision_flag to solve the collision sistuation
  //! number of collision occured
  int collision_count = 0;
  //! boolean to test if there is an collision
  bool collision_flag = false;
  //! boolean to test if collision with Predator
  bool collision_predator_flag = false;

  /**
  * @brief A simgle getter function for light behavior
  */
  Behavior get_light_behavior() {return light_type_; }

  /**
  * @brief A simgle getter function for food behavior
  */
  Behavior get_food_behavior() {return food_type_; }

  /**
  * @brief A simgle getter function for BV behavior
  */ 
  Behavior get_bv_behavior() {return bv_type_; }

  /**
  * @brief A setter function that set the Behavior type to the light behavior
  * alse create new Braitenberg_behaviors class
  *
  * @param[in] type The type that need to set to
  */
  void set_light_behavior(Behavior type) {
    if (light_behavior_ != NULL) {
      delete(light_behavior_);
    }
    switch (type) {
      case kExplore:
      {
        light_behavior_ = new Braitenberg_behavior_explore();
        light_type_ = type;
        break;
      }
      case kCoward:
      {
        light_behavior_ = new Braitenberg_behavior_coward();
        light_type_ = type;
        break;
      }
      case kLove:
      {
        light_behavior_ = new Braitenberg_behavior_love();
        light_type_ = type;
        break;
      }
      case kAggressive:
      {
        light_behavior_ = new Braitenberg_behavior_aggression();
        light_type_ = type;
        break;
      }
      case kNone:
      {
        light_behavior_ = new Braitenberg_behavior_none();
        light_type_ = type;
        break;
      }
      default:
      numBehaviors_--;
      break;
    }
  }

  /**
  * @brief A setter function that set the Behavior type to the food behavior
  * alse create new Braitenberg_behaviors class
  *
  * @param[in] type The type that need to set to
  */
    void set_food_behavior(Behavior type) {
    if (food_behavior_ != NULL) {
      delete(food_behavior_);
    }
    switch (type) {
      case kExplore:
      {
        food_behavior_ = new Braitenberg_behavior_explore();
        food_type_ = type;
        break;
      }
      case kCoward:
      {
        food_behavior_ = new Braitenberg_behavior_coward();
        food_type_ = type;
        break;
      }
      case kLove:
      {
        food_behavior_ = new Braitenberg_behavior_love();
        food_type_ = type;
        break;
      }
      case kAggressive:
      {
        food_behavior_ = new Braitenberg_behavior_aggression();
        food_type_ = type;
        break;
      }
      case kNone:
      {
        food_behavior_ = new Braitenberg_behavior_none();
        food_type_ = type;
        break;
      }
      default:
      numBehaviors_--;
      break;
    }
  }

  /**
  * @brief A setter function that set the Behavior type to the BV behavior
  * alse create new Braitenberg_behaviors class
  *
  * @param[in] type The type that need to set to
  */
    void set_bv_behavior(Behavior type) {
    if (bv_behavior_ != NULL) {
      delete(bv_behavior_);
    }
    switch (type) {
      case kExplore:
      {
        bv_behavior_ = new Braitenberg_behavior_explore();
        bv_type_ = type;
        break;
      }
      case kCoward:
      {
        bv_behavior_ = new Braitenberg_behavior_coward();
        bv_type_ = type;
        break;
      }
      case kLove:
      {
        bv_behavior_ = new Braitenberg_behavior_love();
        bv_type_ = type;
        break;
      }
      case kAggressive:
      {
        bv_behavior_ = new Braitenberg_behavior_aggression();
        bv_type_ = type;
        break;
      }
      case kNone:
      {
        bv_behavior_ = new Braitenberg_behavior_none();
        bv_type_ = type;
        break;
      }
      default:
      numBehaviors_--;
      break;
    }
  }

  /**
  * @brief Notify method used to upadte the wheelvelocity for food,
  * light, and BV
  */
  void Notify() {
    BV_obs_->OnUpdate(light_wheel_velocity, food_wheel_velocity,
      bv_wheel_velocity);
  }

  /**
  * @brief Subscribe the Observer
  *
  * @param[in] sub The Observer of this BV want to update WheelVelocity
  */  
  void Subscribe(Observer * sub) {BV_obs_ = sub;
    subscribe_checker = true;}

  /**
  * @brief Unsubscribe the Observer
  */ 
  void Unsubscribe() {BV_obs_ = NULL; subscribe_checker = false; }

  //! check if the current BV is already subcribe to Observer
  bool subscribe_checker;

  //! starvation_remain_energy
  int starvation_remain_energy;
  //! BV_50_percent_energy_left
  bool BV_50_percent_energy_left = false;
  //! BV_10_percent_energy_left
  bool BV_10_percent_energy_left = false;
  //! BV_0_percent_energy_left
  bool BV_0_percent_energy_left = false;
  //! BV_500_timestep_before_die
  bool BV_500_timestep_before_die = false;
  //! BV_full_energy
  bool BV_full_energy = false;
  //! BV_stop_moving
  bool BV_stop_moving = false;

 protected:
  //! all BV sensors
  std::vector<Pose> light_sensors_;
  //! motion_behavior_
  MotionBehaviorDifferential * motion_behavior_{nullptr};
  //! wheel_velocity_ of BV
  WheelVelocity wheel_velocity_;
  // for all BV behaviors
  //! light_behavior_ of Light
  Braitenberg_behaviors* light_behavior_;
  //! food_behavior_ of Food
  Braitenberg_behaviors* food_behavior_;
  //! bv_behavior_ of BV
  Braitenberg_behaviors* bv_behavior_;
  // behavior types
  //! light_type_ of Light
  Behavior light_type_;
  //! food_type_ of Food
  Behavior food_type_;
  //! bv_type_ of BV
  Behavior bv_type_;
  //! behavior_storage_
  std::vector<Behavior> behavior_storage_;
  //! behavior_vector_iteration_ indexing into storage
  int behavior_vector_iteration_;
  //! keep track of closest_light_entity_
  const ArenaEntity* closest_light_entity_;
  //! keep track of closest_food_entity_
  const ArenaEntity* closest_food_entity_;
  //! keep track of closest_bv_entity_
  const ArenaEntity* closest_bv_entity_;
  //! defaultSpeed_ of BV
  double defaultSpeed_;
  //! numBehaviors_ of BV
  double numBehaviors_;
  //! light_wheel_velocity of BV based of Light
  WheelVelocity light_wheel_velocity;
  //! food_wheel_velocity of Bv based of Food
  WheelVelocity food_wheel_velocity;
  //! bv_wheel_velocity of BV based of BV
  WheelVelocity bv_wheel_velocity;
  //! BV_obs_ observer of BV velocity
  Observer * BV_obs_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_BRAITENBERG_VEHICLE_H_
