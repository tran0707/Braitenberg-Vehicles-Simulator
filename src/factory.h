/**
 * @file factory.h
 *
 * @copyright 2019 tran0707, All rights reserved.
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include "src/arena_entity.h"
#include "src/derived_factory.h"
#include "src/entity_type.h"

#ifndef SRC_FACTORY_H_
#define SRC_FACTORY_H_

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/**
* @brief Factory is an abstract class that used to declare 
* the Create method so that all the derived factories can 
* inherit and used this method.
*/

class Factory {
 public:
Factory();
virtual ~Factory();
/**
* @brief Create is a virtual method to create Food, Light, 
* and BraitenbergVehicle object in Arena
*/
virtual ArenaEntity *Create(__unused json_object* config) = 0;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
#endif  // SRC_FACTORY_H_
