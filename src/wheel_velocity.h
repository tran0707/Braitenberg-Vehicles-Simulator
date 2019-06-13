/**
 * @file wheel_velocity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_WHEEL_VELOCITY_H_
#define SRC_WHEEL_VELOCITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of the position/orientation of an entity
 * within the Arena.
 *
 * NOTE: Origin (0,0) is at the upper left corner of the Arena.
 */
struct WheelVelocity {
 public:
  /**
   * @brief Default constructor. Initialize the pose to (0,0,0)
   */
  WheelVelocity()
    : left(STARTING_VELOCITY), right(STARTING_VELOCITY) {}

  /**
   * @brief Constructor
   *
   * @param l The left wheel_velocity
   * @param r The right wheel_velocity
   */
  WheelVelocity(double l, double r) : left(l), right(r) {}

  /**
   * @brief Constructor
   *
   * @param l The left wheel_velocity
   * @param r The right wheel_velocity
   * @param max The max wheel_velocity
   */
  WheelVelocity(double l, double r, double max) : left(l), right(r) {
    if (left > max) { left = max; }
    if (right > max) { right = max; }
  }

  /**
   * @brief Default assignment operator. Simply copies the (x,y) values of
   * another Pose.
   *
   * @param other The Pose object to copy from.
   *
   * @return The left-hand-side Pose object that is now identical (in value)
   * to `other`.
   */
  WheelVelocity &operator=(const WheelVelocity &other) = default;

  //! left wheel_velocity
  double left;
  //! right wheel_velocity
  double right;

  /**
  * @brief Overload operation function that use to compare two WheelVelocity 
  * object. This will be use in the Braitenberg_vehicle behaviors unit tests.
  * This function can compare two double number with error less than 0.0001
  *
  * @param other The WheelVelocity object that compared with
  *
  * @return The boolean true or false based on the left and right value inside
  * of each objects.
  */
  bool operator==(const WheelVelocity &other){
    double left_compare = this->left - other.left;
    double right_compare = this->right - other.right;
    if ((left_compare < 0.0001 && left_compare > -0.0001) &&
      (right_compare < 0.0001 && right_compare > -0.0001)) {
      return true;
    }
    return false;
  }
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_WHEEL_VELOCITY_H_
