/**
 * @file observer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef SRC_OBSERVER_H_
#define SRC_OBSERVER_H_

#include <sstream>
#include <iomanip>
#include <iostream>
#include "vector"
#include "string"
#include "src/braitenberg_vehicle.h"
#include "src/wheel_velocity.h"
#include "src/graphics_arena_viewer.h"
#include "src/data_box.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An observer class that use to observer wheel velocity
 * for all food, light, and braitenberg_vehicle
 *
 */
class Observer {
 public:
  /**
   * @brief Constructor.
   * This contructor has observer wheel velocity initilize to NULL
   */ 
  Observer(): obs_text_l_vel_(NULL), obs_text_f_vel_(NULL),
  obs_text_bv_vel_(NULL) {}
  virtual ~Observer() {}
  Observer &operator=(const Observer &other) = delete;
  Observer(const Observer &obs) = delete;

  /**
  * @brief Data_Setter uses to set data after observe it from BV,
  * and store it into the private variable of Observer class
  *
  * @param text_l_vel Data for light WheelVelocity
  * @param text_f_vel Data for food WheelVelocity
  * @param text_bv_vel Data for BV WheelVelocity
  */
  void Data_Setter(DataBox * text_l_vel, DataBox * text_f_vel,
    DataBox * text_bv_vel) {
    obs_text_l_vel_ = text_l_vel;
    obs_text_f_vel_ = text_f_vel;
    obs_text_bv_vel_ = text_bv_vel;
  }

  /**
   * @brief OnUpdate This method uses to update the Textbox in GAV
   * each time BV call update on the new change WheelVelocity.
   * 
   * @param l_vel WheelVelocity for light
   * @param f_vel WheelVelocity for food
   * @param bv_vel WheelVelocity for BV
   */
  void OnUpdate(WheelVelocity l_vel, WheelVelocity f_vel,
    WheelVelocity bv_vel) {
    std::string data;
    data = formatValue(l_vel.left);
    obs_text_l_vel_->left->setValue(data);
    data = formatValue(l_vel.right);
    obs_text_l_vel_->right->setValue(data);
    data = formatValue(f_vel.left);
    obs_text_f_vel_->left->setValue(data);
    data = formatValue(f_vel.right);
    obs_text_f_vel_->right->setValue(data);
    data = formatValue(bv_vel.left);
    obs_text_bv_vel_->left->setValue(data);
    data = formatValue(bv_vel.right);
    obs_text_bv_vel_->right->setValue(data);
  }

  /**
   * @brief Converting float to string and set precision to 2
   *
   * @param val The float value that need to convert
   */
  std::string formatValue(float val) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << val;
    return ss.str();
  }

 private:
  DataBox * obs_text_l_vel_;
  DataBox * obs_text_f_vel_;
  DataBox * obs_text_bv_vel_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_OBSERVER_H_
