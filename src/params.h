/**
 * @file params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 */

// graphics
//! X_DIM
#define X_DIM 1024
//! Y_DIM
#define Y_DIM 768
//! TEXT_BOX_WIDTH
#define TEXT_BOX_WIDTH 50
//! GUI_MENU_WIDTH
#define GUI_MENU_WIDTH 190
//! COMBO_BOX_WIDTH
#define COMBO_BOX_WIDTH 150
//! GUI_MENU_GAP
#define GUI_MENU_GAP 10

// entity
//! DEFAULT_POSE
#define DEFAULT_POSE \
  { 200, 200, 0}
//! DEFAULT_COLOR
#define DEFAULT_COLOR \
  { 255, 255, 255 }
//! DEFAULT_RADIUS
#define DEFAULT_RADIUS 20

// mobile entity
//! STARTING_VELOCITY
#define STARTING_VELOCITY 0.0

// robot
//! ROBOT_INIT_POS
#define ROBOT_INIT_POS \
  { 500, 500 , 0}

// braitenberg
//! BV B_MIN_RAD
#define B_MIN_RAD 8
//! BV B_MAX_RAD
#define B_MAX_RAD 14
//! BV BRAITENBERG_COLLISION_DELTA
#define BRAITENBERG_COLLISION_DELTA 1
//! BV BRAITENBERG_COLOR
#define BRAITENBERG_COLOR {122, 0, 25}
//! BV DEF_FOOD_BEHAV
#define DEF_FOOD_BEHAV kLove
//! BV DEF_LIGHT_BEHAV
#define DEF_LIGHT_BEHAV kCoward
//! BV BRAITENBERG_SPEED_CONST
#define BRAITENBERG_SPEED_CONST .0025
//! BV BRAITENBERG_LOVE_AVG_SPEED
#define BRAITENBERG_LOVE_AVG_SPEED 5
//! BV BRAITENBERG_TURNING_CONST
#define BRAITENBERG_TURNING_CONST 20
//! BV BRAITENBERG_VEHICLE_COUNT
#define BRAITENBERG_VEHICLE_COUNT 1
//! BV BRAITENBERG_RATIO
#define BRAITENBERG_RATIO .5

// light_sensor
//! SENSOR_LIGHT_RAD
#define SENSOR_LIGHT_RAD 4

// food
//! FOOD_RADIUS
#define FOOD_RADIUS 20
//! FOOD_COLLISION_DELTA
#define FOOD_COLLISION_DELTA 1
//! FOOD_INIT_POS
#define FOOD_INIT_POS \
  { 400, 400 }
//! FOOD_COLOR
#define FOOD_COLOR \
  { 0, 255, 0 }
//! N_FOOD
#define N_FOOD 1
//! WITH_FOOD_DEFAULT
#define WITH_FOOD_DEFAULT true

// light
//! LIGHT_POSITION
#define LIGHT_POSITION \
  { 200, 200 }
//! LIGHT_RADIUS
#define LIGHT_RADIUS 30
//! LIGHT_MIN_RADIUS
#define LIGHT_MIN_RADIUS 10
//! LIGHT_MAX_RADIUS
#define LIGHT_MAX_RADIUS 30
//! LIGHT_COLOR
#define LIGHT_COLOR \
  { 255, 255, 255 }

// added
//! PREDATOR_COLOR
#define PREDATOR_COLOR {255, 0, 0}

#endif  // SRC_PARAMS_H_
