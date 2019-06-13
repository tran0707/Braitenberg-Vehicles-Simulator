/**
 * @file predator.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/predator.h"
#include "src/params.h"
#include "src/braitenberg_behaviors.h"
#include "src/braitenberg_behavior_explore.h"
#include "src/braitenberg_behavior_aggression.h"
#include "src/braitenberg_behavior_coward.h"
#include "src/braitenberg_behavior_love.h"
#include "src/braitenberg_vehicle.h"

class SensorLightLove;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

int Predator::count = 0;
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

Predator::Predator() :
collision_count(0), collision_flag(false),
light_sensors_(), wheel_velocity_(),
light_behavior_(new Braitenberg_behavior_coward()),
food_behavior_(new Braitenberg_behavior_none()),
bv_behavior_(new Braitenberg_behavior_aggression()),
predator_behavior_(new Braitenberg_behavior_none()),
closest_light_entity_(NULL), closest_food_entity_(NULL),
closest_bv_entity_(NULL), closest_predator_entity_(NULL),
defaultSpeed_(5.0), numBehaviors_(3), collision_with_bv(false) {
  set_type(kPredator);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(PREDATOR_COLOR);
  set_pose(ROBOT_INIT_POS);

  wheel_velocity_ = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);
}
void Predator::TimestepUpdate(__unused unsigned int dt) {
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
  }
  UpdateLightSensors();
}

void Predator::HandleCollision(__unused EntityType ent_type,
 __unused ArenaEntity * object) {
  if (ent_type == kBraitenberg) {
    set_heading(static_cast<int>((get_pose().theta + 0)) % 360);
    collision_flag = false;
    collision_with_bv = true;
    static_cast<BraitenbergVehicle*>(object)->HandleCollision(kPredator);
  } else {
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
    collision_flag = true;
    collision_with_bv = false;
  }
}

void Predator::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    if (entity.get_id() != this->get_id()) {
      closest_entity_ = &closest_bv_entity_;
    }
  } else if (entity.get_type() == kPredator) {
    if (entity.get_id() != this->get_id()) {
      closest_entity_ = &closest_predator_entity_;
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

void Predator::Update() {
  // WheelVelocity for light_behavior_
  WheelVelocity light_wheel_velocity = WheelVelocity(0, 0);
  light_wheel_velocity = light_behavior_->cal_wheel_velocity(
  closest_light_entity_, defaultSpeed_, light_sensors_);
  // WheelVelocity for food_behavior_
  WheelVelocity food_wheel_velocity = WheelVelocity(0, 0);
  food_wheel_velocity = food_behavior_->cal_wheel_velocity(
  closest_food_entity_, defaultSpeed_, light_sensors_);

  // WheelVelocity for bv_behavior_
  WheelVelocity bv_wheel_velocity = WheelVelocity(0, 0);
  bv_wheel_velocity = bv_behavior_->cal_wheel_velocity(
  closest_bv_entity_, defaultSpeed_, light_sensors_);

  // WheelVelocity for bv_behavior_
  WheelVelocity predator_wheel_velocity = WheelVelocity(0, 0);
  predator_wheel_velocity = predator_behavior_->cal_wheel_velocity(
  closest_predator_entity_, defaultSpeed_, light_sensors_);

  // calculate the speed
  if (numBehaviors_ != 0) {
    // if bv behavior set to Default
    if (bv_wheel_velocity.left == 0 && bv_wheel_velocity.right == 0) {
      numBehaviors_ = 2;
      wheel_velocity_ = WheelVelocity(
        (light_wheel_velocity.left +
          food_wheel_velocity.left +
          bv_wheel_velocity.left +
          predator_wheel_velocity.left)/numBehaviors_,
        (light_wheel_velocity.right +
          food_wheel_velocity.right +
          bv_wheel_velocity.right +
          predator_wheel_velocity.right)/numBehaviors_,
        defaultSpeed_);
    } else {  // if bv behavior enable
      numBehaviors_ = 3;
      wheel_velocity_ = WheelVelocity(
        (light_wheel_velocity.left +
          food_wheel_velocity.left +
          bv_wheel_velocity.left +
          predator_wheel_velocity.left)/numBehaviors_,
        (light_wheel_velocity.right +
          food_wheel_velocity.right +
          bv_wheel_velocity.right +
          predator_wheel_velocity.right)/numBehaviors_,
        defaultSpeed_);
    }
  } else {
    wheel_velocity_ = WheelVelocity(0, 0);
  }
}

std::string Predator::get_name() const {
  return "Predator " + std::to_string(get_id());
}

std::vector<Pose> Predator::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> Predator::get_light_sensors() {
  return light_sensors_;
}

void Predator::UpdateLightSensors() {
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

void Predator::LoadFromObject(json_object* config) {
  json_object entity_config = *config;
  ArenaEntity::LoadFromObject(config);

  set_light_behavior();
  set_food_behavior();
  set_bv_behavior();
  set_predator_behavior();

  UpdateLightSensors();
}

bool Predator::is_collision_with_bv() {
  if (collision_with_bv == true) {
    collision_with_bv = false;
    return true;
  }
  return false;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
