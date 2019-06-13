/**
 * @file bv_decorator.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_BV_DECORATOR_H_
#define SRC_BV_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An Entity of Predator that can disguise as BV but still be able to
 * cosume Braitenberg Vehicle
 */
class BraitenbergVehicle_Decorator : public BraitenbergVehicle {
/**
 * @brief This class used to decorate the Predator to BraitenbergVehicle.
 * It makes Predator act exactly like BV and come back to itself after
 * collision (eat) another BV.
 */	
 public:
  	/**
   	* @brief BraitenbergVehicle_Decorator's constructor.
   	* 
   	* @param predator It is the pointer of class Predator.
   	*/
BraitenbergVehicle_Decorator(Predator *predator): BraitenbergVehicle(),
predator_(predator), bv_collision_flag_(false), type_(kPredator_Deco_BV) {
set_type(kPredator_Deco_BV);
}

  	/**
   	* @brief BraitenbergVehicle_Decorator's destructor.
   	*/
~BraitenbergVehicle_Decorator() {}

  	/**
   	* @brief Under certain circumstance, the compiler requires that the
   	* assignment operator is not defined. This `deletes` the default
   	* assignment operator.
   	*/
BraitenbergVehicle_Decorator(const BraitenbergVehicle_Decorator & bd) = delete;
BraitenbergVehicle_Decorator operator=
(const BraitenbergVehicle_Decorator &bd) = delete;

  	/**
   	* @brief This function helps Arena to check that any of entities collision
   	* with BV
   	*/
bool is_collision_with_bv() override {
if(bv_collision_flag_ == true) {
bv_collision_flag_ = false;
return true;
}
return false;
}

	/**
	* @brief Handle Collision with BV and Wall
	*
	* @param ent_type Type of the entity that this Decorator collision with
	* @param object The object of this class collision with.
	*/
void HandleCollision(EntityType ent_type, ArenaEntity *object = NULL) override {
if (ent_type == kBraitenberg) {
set_heading(static_cast<int>((get_pose().theta + 0)) % 360);
bv_collision_flag_ = true;
collision_predator_flag = true;
collision_flag = false;
static_cast<BraitenbergVehicle *>(object)->HandleCollision(kPredator_Deco_BV);
} else {
set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
bv_collision_flag_ = false;
collision_flag = true;
}
}

 private:
Predator *predator_{nullptr};
bool bv_collision_flag_;
EntityType type_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_BV_DECORATOR_H_
