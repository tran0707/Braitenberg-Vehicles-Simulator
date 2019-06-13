/**
 * @file food.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

int Food::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Food::Food() : ArenaImmobileEntity() {
  set_type(kFood);
  set_color(FOOD_COLOR);
  set_pose(FOOD_INIT_POS);
  set_radius(FOOD_RADIUS);

  // Set ID
  count++;
  set_id(count);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Food::Reset() {
  set_pose(FOOD_INIT_POS);
} /* Reset */

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
