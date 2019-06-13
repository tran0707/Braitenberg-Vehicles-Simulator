/**
 * @file motion_behavior_differential.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionBehaviorDifferential::UpdatePose(double dt, WheelVelocity vel) {
  double x_prime, y_prime, theta_prime;

  // Get the current pose (position and heading of the composing entity)
  struct Pose pose = entity_->get_pose();
  // Store the velocity for other functions to use during this calculation.
  temp_vel_ = vel;

  // If there is a difference between wheel speeds, use differential drive
  // model to calculate new pose.
  if (std::fabs(temp_vel_.left - temp_vel_.right) > 0) { /* general case */
    struct Pose icc = calc_icc(pose);
    // This can be used for debugging to improve motion control
    if (0) {
      printf("radius: %f\n", radius_);
      printf("vr: %f vl: %f Omega: %f\n",
        temp_vel_.right, temp_vel_.left, omega());
      printf("icc radius: %f\n", icc_radius());
      printf("icc: %f %f\n", icc.x, icc.y);
    }
    // Foodd on differential drive model cited in the header.
    x_prime = (pose.x - icc.x) * std::cos(omega() * dt) +
              (pose.y - icc.y) * -std::sin(omega() * dt) + icc.x;
    y_prime = (pose.x - icc.x) * std::sin(omega() * dt) +
              (pose.y - icc.y) * std::cos(omega() * dt) + icc.y;
    theta_prime = pose.theta + omega() * dt;
  } else {
    // V_r = V_l. Drive straight in the direction of thet heading.
    x_prime = pose.x + std::cos(deg2rad(pose.theta)) * vel.left * dt;
    y_prime = pose.y + std::sin(deg2rad(pose.theta)) * vel.left * dt;
    theta_prime = pose.theta;
  }
  entity_->set_pose(Pose(x_prime, y_prime, theta_prime));
} /* UpdatePose */

struct Pose MotionBehaviorDifferential::calc_icc(struct Pose pose) const {
  return Pose(pose.x - icc_radius() * std::sin(deg2rad(pose.theta)),
              pose.y + icc_radius() * std::cos(deg2rad(pose.theta)));
} /* calc_icc() */

double MotionBehaviorDifferential::icc_radius() const {
  /*
   * Assuming a radius of 0.5, regardless of radius of actual entity. Otherwise
   * things look weird.
   */
  return (0.5 *
    (temp_vel_.left + temp_vel_.right)/(temp_vel_.left - temp_vel_.right));
} /* icc_radius() */

double MotionBehaviorDifferential::omega() const {
  /*
   * Assuming a radius of 0.5, regardless of radius of actual entity. Otherwise
   * things look weird.
   */
  return (temp_vel_.left - temp_vel_.right) / 0.5;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
