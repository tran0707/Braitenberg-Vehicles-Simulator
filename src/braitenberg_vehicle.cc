/**
 * @file braitenberg_vehicle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/braitenberg_vehicle.h"
#include "src/params.h"
#include "src/braitenberg_behaviors.h"
#include "src/braitenberg_behavior_explore.h"
#include "src/braitenberg_behavior_aggression.h"
#include "src/braitenberg_behavior_coward.h"
#include "src/braitenberg_behavior_love.h"

class SensorLightLove;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

int BraitenbergVehicle::count = 0;
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

BraitenbergVehicle::BraitenbergVehicle() :
collision_count(0), collision_flag(false), collision_predator_flag(false),
subscribe_checker(false), starvation_remain_energy(600),
BV_50_percent_energy_left(false), BV_10_percent_energy_left(false),
BV_0_percent_energy_left(false), BV_500_timestep_before_die(false),
BV_full_energy(false), BV_stop_moving(false),
light_sensors_(), wheel_velocity_(),
light_behavior_(new Braitenberg_behavior_none()),
food_behavior_(new Braitenberg_behavior_none()),
bv_behavior_(new Braitenberg_behavior_none()),
light_type_(kNone), food_type_(kNone), bv_type_(kNone),
behavior_storage_(), behavior_vector_iteration_(0),
closest_light_entity_(NULL), closest_food_entity_(NULL),
closest_bv_entity_(NULL), defaultSpeed_(5.0), numBehaviors_(0),
light_wheel_velocity(WheelVelocity(0, 0)),
food_wheel_velocity(WheelVelocity(0, 0)),
bv_wheel_velocity(WheelVelocity(0, 0)),
BV_obs_(new Observer()) {
  set_type(kBraitenberg);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(BRAITENBERG_COLOR);
  set_pose(ROBOT_INIT_POS);

  wheel_velocity_ = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);
}

void BraitenbergVehicle::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
    motion_behavior_->UpdatePose(dt, wheel_velocity_);
    if (collision_flag) {
      collision_count++;
      if (collision_count == 20) {
        set_heading(static_cast<int>((get_pose().theta - 135)) % 360);
        collision_count = 0;
        collision_flag = false;
      }
    }
    // starvation BV timestep
    starvation_remain_energy--;
    if (starvation_remain_energy == 400) {
      BV_50_percent_energy_left = true;
      BV_10_percent_energy_left = false;
      BV_0_percent_energy_left = false;
      BV_500_timestep_before_die = false;
    } else if (starvation_remain_energy == 200) {
      BV_50_percent_energy_left = false;
      BV_10_percent_energy_left = true;
      BV_0_percent_energy_left = false;
      BV_500_timestep_before_die = false;
    } else if (starvation_remain_energy == 0) {
      BV_50_percent_energy_left = false;
      BV_10_percent_energy_left = false;
      BV_0_percent_energy_left = true;
      BV_500_timestep_before_die = false;
    } else if (starvation_remain_energy < -400) {
      BV_50_percent_energy_left = false;
      BV_10_percent_energy_left = false;
      BV_0_percent_energy_left = false;
      BV_500_timestep_before_die = true;
    }
  } else {
    std::cout << "BV_NOO_UPDATE" <<std::endl;
  }
  UpdateLightSensors();
}

void BraitenbergVehicle::HandleCollision(__unused EntityType ent_type,
 __unused ArenaEntity * object) {
  if (ent_type == kPredator || ent_type == kPredator_Deco_BV ||
    ent_type == kPredator_Deco_Food || ent_type == kPredator_Deco_Light) {
    collision_predator_flag = true;
    collision_flag = false;
  } else if (ent_type == kFood) {
    BV_full_energy = true;
    starvation_remain_energy = 600;
  } else {
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
    collision_flag = true;
  }
}

void BraitenbergVehicle::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    if (entity.get_id() != this->get_id()) {
      closest_entity_ = &closest_bv_entity_;
    }
  }

  if (!closest_entity_) {
    return;
  }

  if (!*closest_entity_) {
    *closest_entity_ = &entity;
  }

  double distance = (this->get_pose()-entity.get_pose()).Length();
  double closest_distance =
  (this->get_pose()-(*closest_entity_)->get_pose()).Length();
  if (distance < closest_distance) {
    *closest_entity_ = &entity;
    closest_distance = distance;
  }
  if (closest_distance > 100.0) {
    *closest_entity_ = NULL;
  }
}

/**
 * @brief update BraitenbergVehicle's behavior
 * this function will change wheel speed and color of robots
 * based on the light and food sensors
 */
void BraitenbergVehicle::Update() {
  if (collision_predator_flag == true) {
    set_color(RgbColor(kGhost));
    set_type(kDeadBV);
    BV_stop_moving = true;
  }
  if (BV_50_percent_energy_left == true &&
    BV_10_percent_energy_left == false &&
    BV_0_percent_energy_left == false &&
    BV_500_timestep_before_die == false) {
    set_color(RgbColor(kEnergyLevel3));
    set_light_behavior(kNone);
    set_food_behavior(kExplore);
    set_bv_behavior(kNone);
    BV_50_percent_energy_left = false;
    BV_stop_moving = false;
  } else if (BV_50_percent_energy_left == false &&
    BV_10_percent_energy_left == true &&
    BV_0_percent_energy_left == false &&
    BV_500_timestep_before_die == false) {
    set_color(RgbColor(kEnergyLevel2));
    set_light_behavior(kNone);
    set_food_behavior(kLove);
    set_bv_behavior(kNone);
    BV_10_percent_energy_left = false;
    BV_stop_moving = false;
  } else if (BV_50_percent_energy_left == false &&
    BV_10_percent_energy_left == false &&
    BV_0_percent_energy_left == true &&
    BV_500_timestep_before_die == false) {
    set_color(RgbColor(kEnergyLevel1));
    set_light_behavior(kNone);
    set_food_behavior(kAggressive);
    set_bv_behavior(kNone);
    BV_0_percent_energy_left = false;
    BV_stop_moving = false;
  } else if (BV_50_percent_energy_left == false &&
    BV_10_percent_energy_left == false &&
    BV_0_percent_energy_left == false &&
    BV_500_timestep_before_die == true) {
    set_color(RgbColor(kGhost));
    set_type(kDeadBV);
    BV_stop_moving = true;
  } else if (BV_full_energy == true) {
    set_color(BRAITENBERG_COLOR);
    set_light_behavior(behavior_storage_[0]);
    set_food_behavior(behavior_storage_[1]);
    set_bv_behavior(behavior_storage_[2]);
    BV_full_energy = false;
    BV_stop_moving = false;
  }
  if (BV_stop_moving == true) {
    wheel_velocity_ = WheelVelocity(0, 0);
  } else {
  // WheelVelocity for light_behavior_
  light_wheel_velocity = light_behavior_->cal_wheel_velocity(
  closest_light_entity_, defaultSpeed_, light_sensors_);
  if (light_wheel_velocity.left != 0 || light_wheel_velocity.right != 0) {
    numBehaviors_++;
  }
  // WheelVelocity for food_behavior_
  food_wheel_velocity = food_behavior_->cal_wheel_velocity(
  closest_food_entity_, defaultSpeed_, light_sensors_);
  if (food_wheel_velocity.left != 0 || food_wheel_velocity.right != 0) {
    numBehaviors_++;
  }
  // WheelVelocity for bv_behavior_
  bv_wheel_velocity = bv_behavior_->cal_wheel_velocity(
    closest_bv_entity_, defaultSpeed_, light_sensors_);
  if (bv_wheel_velocity.left != 0 || bv_wheel_velocity.right != 0) {
    numBehaviors_++;
  }
  if (numBehaviors_ == 0) {
    wheel_velocity_ = WheelVelocity(0, 0);
  } else {
  // dynamic calculate the speed based on the reading of each BV
    wheel_velocity_ = WheelVelocity(
      (light_wheel_velocity.left + food_wheel_velocity.left
        + bv_wheel_velocity.left)/numBehaviors_,
      (light_wheel_velocity.right + food_wheel_velocity.right
        + bv_wheel_velocity.right)/numBehaviors_,
      defaultSpeed_);
    // reset numBehaviors_
    numBehaviors_ = 0;
  }
}
  // Notify Observer for the new WheelVelocity
  if (subscribe_checker == true) {
    Notify();
  }
}

std::string BraitenbergVehicle::get_name() const {
  return "Braitenberg " + std::to_string(get_id());
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors() {
  return light_sensors_;
}

void BraitenbergVehicle::UpdateLightSensors() {
  for (unsigned int f = 0; f < light_sensors_.size(); f++) {
    Pose& pos = light_sensors_[f];
    if (f == 0) {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta - 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta - 40));
    } else {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta + 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta + 40));
    }
  }
}

void BraitenbergVehicle::LoadFromObject(json_object* config) {
  json_object entity_config = *config;
  ArenaEntity::LoadFromObject(config);

  if (entity_config.find("light_behavior") != entity_config.end()) {
    light_type_ = get_behavior_type(
      entity_config["light_behavior"].get<std::string>());
      set_light_behavior(light_type_);
  }
  if (entity_config.find("food_behavior") != entity_config.end()) {
    food_type_ = get_behavior_type(
      entity_config["food_behavior"].get<std::string>());
      set_food_behavior(food_type_);
  }
  if (entity_config.find("bv_behavior") != entity_config.end()) {
    bv_type_ = get_behavior_type(
      entity_config["bv_behavior"].get<std::string>());
    set_bv_behavior(bv_type_);
  }

  // This save the all behavior when the first LoadFromObject called
  if (behavior_vector_iteration_ == 0) {
    behavior_storage_.push_back(light_type_);
    behavior_storage_.push_back(food_type_);
    behavior_storage_.push_back(bv_type_);
    behavior_vector_iteration_++;
  }

  UpdateLightSensors();
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
