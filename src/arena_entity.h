/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_H_
#define SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A food class from which all Arena entities inherit.
 *
 * All entities know how to:
 *
 * 1. Update themselves at each timestep (i.e. in accordance with current
 * velocity and position).
 *
 * 2. Reset themselves to a newly constructed state. So that the user can
 * click the reset button to restart the game. Alternatively, the game
 * will be reset if the robot has won/lost.
 *
 * Please note that here use the upper-left coordinate, which means that the
 * origin point (0.0,0.0) is at the upper left.
 *
 * All arena entities are circular.
 *
 */
class ArenaEntity {
 public:
  /**
 * @brief ArenaEntity constructor initialized with default values from params.h
 */
  ArenaEntity() : pose_(DEFAULT_POSE), color_(DEFAULT_COLOR) {}

  /**
   * @brief Default destructor -- as defined by compiler.
   */
  virtual ~ArenaEntity() = default;

  /**
   * @brief Perform whatever updates needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   *
   * @param[in] dt is time elapsed since the last update. Unused.
   */
  virtual void TimestepUpdate(__unused unsigned int dt) {}

  /**
   * @brief Reset entity to a newly constructed state.
   */
  virtual void Reset() {}

  /**
   * @brief Method for updating the arena
   */
  virtual void Update() {
  }

  /**
   * @brief Get the name of the entity for visualization and for debugging.
   *
   * @return Name of the entity. Each entity type hard codes its name
   * (e.g. "Robot").
   */
  virtual std::string get_name() const = 0;

  /**
  * @brief Function to get position of Entity
  */
  const Pose &get_pose() const { return pose_; }

  /**
  * @brief Function to set position of Entity
  *
  * @param pose The position want to set
  */
  void set_pose(const Pose &pose) { pose_ = pose; }

  /**
   * @brief Setter method for position within entity pose variable.
   *
   * @param inx The x position want to set
   * @param iny The y position want to set
   */
  void set_position(const double inx, const double iny) {
    pose_.x = inx;
    pose_.y = iny;
  }

  /**
   * @brief Setter method for heading within entity pose variable.
   *
   * @param t The angle that want to set
   */
  void set_heading(const double t) {pose_.theta = t;}

  /**
   * @brief Setter for heading within pose, but change is relative to current
   * value.
   *
   * @param[in] delta by which to modify current heading. Can be positive
   * or negative.
   */
  void RelativeChangeHeading(const double delta) {
    pose_.theta += delta;
  }

  /**
  * @brief Getter function to get color
  */
  const RgbColor &get_color() const { return color_; }

  /**
  * @brief Setter function to set color
  *
  * @param color The color that want to set
  */
  void set_color(const RgbColor &color) { color_ = color; }

  /**
  * @brief Getter function to get radius
  */
  double get_radius() const { return radius_; }

  /**
  * @brief Setter function to set radius
  *
  * param radius The radius that want to set
  */
  void set_radius(double radius) { radius_ = radius; }

  /**
  * @brief Getter function to get type of Entity
  */
  EntityType get_type() const { return type_; }

  /**
  * @brief Setter function to set type of Entity
  *
  * @param et The new type that want to set
  */
  void set_type(EntityType et) { type_ = et; }

  /**
  * @brief Getter function to set ID
  */
  int get_id() const { return id_; }

  /**
  * @brief Setter function to set ID
  *
  * @param id The new id that want to set
  */
  void set_id(int id) { id_ = id; }

  /**
   * @brief Getter method for determining if entity can move or not.
   */
  bool is_mobile(void) { return is_mobile_; }

  /**
   * @brief Setter method for indicating if entity can move or not.
   */
  void set_mobility(bool value) { is_mobile_ = value; }

  /**
  * @brief Function that Load object from Json file
  *
  * @param config The config from Json file
  */
  virtual void LoadFromObject(json_object* config) {
    json_object entity_config = *config;
    set_position(
      entity_config["x"].get<double>(), entity_config["y"].get<double>());
    if (entity_config.find("theta") != entity_config.end()) {
      pose_.theta = entity_config["theta"].get<double>();
    }
    if (entity_config.find("r") != entity_config.end()) {
      set_radius(entity_config["r"].get<double>());
    }
  }

  /**
  * @brief Used to handle collision between Entities
  *
  * @param ent_type The type of entites collision with
  * @param object The object that collision with
  */
  virtual void HandleCollision(__unused EntityType ent_type,
                               __unused ArenaEntity * object = NULL) { }

  /**
  * @brief Used to check collision with entities with BV
  */
  virtual bool is_collision_with_bv() {return false;}

 private:
  double radius_{DEFAULT_RADIUS};
  Pose pose_;
  RgbColor color_;
  EntityType type_{kEntity};
  int id_{-1};
  bool is_mobile_{false};
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_ENTITY_H_
