/**
 * @file entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/common.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

//! EntityType All Entity type exist in this simulation
enum EntityType {
  kLight = 0, kFood, kEntity, kBraitenberg,
  kRightWall, kLeftWall, kTopWall, kBottomWall,
  kUndefined, kPredator, kDeadBV, kDeadPredator,
  kPredator_Deco_Light, kPredator_Deco_Food, kPredator_Deco_BV
};

/**
* @brief The function that return type of Entity based on the string input
*
* @param type A input string type of Entity
*/
inline EntityType get_entity_type(const std::string& type) {
  if (type == "Light") {
    return kLight;
  }
  if (type == "Food") {
    return kFood;
  }
  if (type == "Braitenberg") {
    return kBraitenberg;
  }
  // added
  if (type == "Predator") {
    return kPredator;
  }
  if (type == "Predator_Deco_BV") {
    return kPredator_Deco_BV;
  }
  if (type == "Predator_Deco_Food") {
    return kPredator_Deco_Food;
  }
  if (type == "kPredator_Deco_Light") {
    return kPredator_Deco_Light;
  }
  return kUndefined;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_TYPE_H_
