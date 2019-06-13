/**
 * @file food_decorator.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_DECORATOR_H_
#define SRC_FOOD_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);
/**
 * @brief This class used to decorate the Predator to Food.
 * It makes Predator act exactly like Food and come back to itself after
 * collision (eat) another BV.
 */	
class Food_Decorator : public Food {
 public:
  	/**
   	* @brief Food_Decorator's constructor.
   	* 
   	* @param predator It is the pointer of class Predator.
   	*/
Food_Decorator(Predator *predator): Food(), predator_(predator),
bv_collision_flag_(false), type_(kPredator_Deco_Food) {
set_type(kPredator_Deco_Food);
}

  	/**
   	* @brief Food's destructor.
   	*/
~Food_Decorator() {}

  	/**
   	* @brief Under certain circumstance, the compiler requires that the
   	* assignment operator is not defined. This `deletes` the default
   	* assignment operator.
   	*/
Food_Decorator(const Food_Decorator &fd) = delete;
Food_Decorator operator=(const Food_Decorator &fd) = delete;

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
bv_collision_flag_ = true;
static_cast<BraitenbergVehicle *>(object)->HandleCollision(kPredator_Deco_Food);
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
#endif  // SRC_FOOD_DECORATOR_H_
