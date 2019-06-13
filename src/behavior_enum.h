/**
 * @file behavior_enum.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
#include <string>

#ifndef SRC_BEHAVIOR_ENUM_H_
#define SRC_BEHAVIOR_ENUM_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Enumeration
 ******************************************************************************/
/**
 * @brief Enumeration representing the 4 possible behaviors
 *
 */

enum Behavior {
  kNone = 0,
  kAggressive,
  kCoward,
  kExplore,
  kLove
};

/**
* @brief Function to get behavior type based on the string input
*/
inline Behavior get_behavior_type(const std::string& type) {
  if (type == "Aggressive") {
    return kAggressive;
  }
  if (type == "Love") {
    return kLove;
  }
  if (type == "Coward") {
    return kCoward;
  }
  if (type == "Explore") {
    return kExplore;
  }
  return kNone;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_ENUM_H_
