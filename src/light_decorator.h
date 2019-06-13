/**
 * @file light_decorator.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_DECORATOR_H_
#define SRC_LIGHT_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/light.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An Entity of Predator that can disguise as Light but still be able to
 * cosume Braitenberg Vehicle
 */
class Light_Decorator : public Light {
 public:
/**
 * @brief This class used to decorate the Predator to Light.
 * It makes Predator act exactly like BV and come back to itself after
 * collision (eat) another BV.
 */
Light_Decorator(Predator *predator): Light(), predator_(predator),
bv_collision_flag_(false), type_(kPredator_Deco_Light) {
set_type(kPredator_Deco_Light);
}

  	/**
   	* @brief Light_Decorator's destructor.
   	*/
~Light_Decorator() {}

  	/**
   	* @brief Under certain circumstance, the compiler requires that the
   	* assignment operator is not defined. This `deletes` the default
   	* assignment operator.
   	*/
Light_Decorator(const Light_Decorator & ld) = delete;
Light_Decorator operator=(const Light_Decorator & ld) = delete;

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
static_cast<BraitenbergVehicle *>(object)->
HandleCollision(kPredator_Deco_Light);
} else {
set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
bv_collision_flag_ = false;
}
}

 private:
Predator *predator_{nullptr};
bool bv_collision_flag_;
EntityType type_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_LIGHT_DECORATOR_H_
