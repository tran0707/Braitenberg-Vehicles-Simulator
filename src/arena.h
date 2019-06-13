/**
 * @file arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

#include "src/predator.h"
#include "src/common.h"
#include "src/food.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many entities
 * running around.
 *
 * While GraphicsArenaViewer handles the graphics, Arena handles all the
 * data and all the entities (it is the model of MVC). It manages the
 * interaction among the entities in the Arena.
 *
 */

class Arena {
 public:
  /**
   * @brief Arena's constructor.
   * Initialize all private variables and entities.
   */
  Arena();

  /**
   * @brief Another Arena's constructor.
   *
   * @param arena_object The Json Object 
   * @param csv_ext Boolean used to check if the args input is csv file
   * @param json_ext Boolean used to check if the arfs inout is json file
   * @param json_x_dim The args for json xdim
   * @param json_y_dim The args for hson ydim
   */
  explicit Arena(json_object* arena_object, bool csv_ext, bool json_ext,
   double json_x_dim, double json_y_dim);

  /**
   * @brief Arena's destructor. `delete` all entities created.
   */
  ~Arena();

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by. This is
   * practically unused because the arena state is advanced
   * incrementally at a fixed rate.
   *
   * If `dt == 0`, `return` immediately. Otherwise calls
   * Arena::UpdateEntitiesTimestep() once.
   */
  void AdvanceTime(double dt);

  /**
  * @brief Function to add new Entity into Arena Object
  *
  * @param entity The new Entity that want to add
  */
  void AddEntity(ArenaEntity* entity);

  /**
   * @brief Reset all entities in Arena.
   */
  void Reset();

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Arena &operator=(const Arena &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Arena(const Arena &other) = delete;

  /**
   * @brief Determine if two entities have collided in the Arena. Collision is
   * defined as the distance between two entities being less than the sum of
   * their radii.
   *
   * @param mobile_e This entity is definitely moving.
   * @param other_e This entity might be mobile or immobile.
   *
   */
  bool IsColliding(
    ArenaMobileEntity * const mobile_e, ArenaEntity * const other_e);

  /**
  * @brief Move the mobile entity to the edge of the other without overlap.
  * Without this, entities tend to get stuck inside one another.
  **/
  void AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
    ArenaEntity *const other_e);

  /**
   * @brief Determine if a particular entity has gone out of the boundaries of
   * the simulation (i.e. has collided with any one of the walls).
   *
   * @param ent The entity to check.
   *
   * The checked entity's position will be updated to a "back-off position" so
   * that it won't get stuck into a wall. The calculation of the "back-off
   * position" is technically not accurate, but good enough for our purpose.
   */
  EntityType GetCollisionWall(ArenaMobileEntity * const ent);

  /**
  * @brief Move the entity to the edge of the wall without overlap.
  * Without this, entities tend to get stuck in walls.
  **/
  void AdjustWallOverlap(ArenaMobileEntity * const ent, EntityType wall);


  /**
   * @brief Update all entities for a single timestep.
   *
   * First calls each entity's TimestepUpdate method to update their speed,
   * heading angle, and position. Then check for collisions between entities
   * or between an entity and a wall.
   */
  void UpdateEntitiesTimestep();

  /**
  * @brief The getter function that retunr the Vector of all Arena Entity
  */
  std::vector<class ArenaEntity *> get_entities() const { return entities_; }

  /**
  * @brief Get X dim from specific Arena Entity
  */
  double get_x_dim() { return x_dim_; }

  /**
  * @brief Get X dim from specific Arena Entity
  */
  double get_y_dim() { return y_dim_; }

  /**
   * @brief Random Function to choose 1 in 3 entities
   *
   * @param identity The vector of entities that random choose
   */
  int rand_identity(std::vector<EntityType> identity);

 private:
  // Dimensions of graphics window inside which entities must operate
  double x_dim_;
  double y_dim_;

  // All entities mobile and immobile.
  std::vector<class ArenaEntity *> entities_;

  // A subset of the entities -- only those that can move (only Robot for now).
  std::vector<class ArenaMobileEntity *> mobile_entities_;

  // create Predator
  Predator *predator_container_1;
  Predator *predator_container_2;
  Predator *predator_entity;
  int iteration_count_;
  std::vector<EntityType> random_entities;
  bool is_deco_food;
  bool is_deco_light;
  bool is_deco_bv;
  bool is_dead_pre;
  bool ready_to_deco;
  int index_saved_ent2;
  Pose current_pose;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
