/**
 * @file pose.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_POSE_H_
#define SRC_POSE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/common.h"

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
struct Pose {
 public:
  /**
   * @brief Default constructor. Initialize the pose to (0,0,0)
   */
  Pose() {}

  /**
   * @brief Constructor
   *
   * @param in_x The X component of the Pose.
   * @param in_y The Y component of the Pose.
   */
  Pose(double in_x, double in_y) : x(in_x), y(in_y) {}

  /**
   * @brief Constructor
   *
   * @param in_x The X component of the Pose.
   * @param in_y The Y component of the Pose.
   * @param in_theta The angle component of the Pose.
   */
  Pose(double in_x, double in_y, double in_theta)
      : x(in_x),
        y(in_y),
        theta(in_theta) {}

  /**
   * @brief Default assignment operator. Simply copies the (x,y) values of
   * another Pose.
   *
   * @param other The Pose object to copy from.
   *
   * @return The left-hand-side Pose object that is now identical (in value)
   * to `other`.
   */
  Pose &operator=(const Pose &other) = default;

  /**
   * @brief Overloaded - operator. Treats the poses as vectors, returns the difference of the two.
   *
   * @param rhs The Pose object on the right hand side of the - operator.
   *
   * @return The Pose of the vector difference of the two vectors.
   **/
  Pose operator-(const Pose &rhs) const {
    double x_new = x - rhs.x;
    double y_new = y - rhs.y;
    double theta_new = theta - rhs.theta;
    return Pose(x_new, y_new, theta_new);
  }

  /**
   * @brief Length. Returns the length of a Pose.
   **/
  double Length() const {
    return sqrt(pow(x, 2) + pow(y, 2));
  }
  //! x pose
  double x{0};
  //! y pose
  double y{0};
  //! theta of pose
  double theta{0.0};
};

/*******************************************************************************
 * Forward Decls
 ******************************************************************************/
/**
* @brief Function to conver deg to rad
*
* @param deg The args degree
*/
constexpr double deg2rad(double deg) { return deg * M_PI / 180.0; }

/**
* @brief Function to convert rad to deg
*
* @param rad The args rad
*/
constexpr double rad2deg(double rad) { return rad * 180.0 / M_PI; }

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_POSE_H_
