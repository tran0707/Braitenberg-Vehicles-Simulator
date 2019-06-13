/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/controller.h"
#include "src/graphics_arena_viewer.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
/**
* @param argc The number of args input
* @param argv The string of args input
*/
int main(__unused int argc, __unused char **argv) {
  // The controller creates both the arena and viewer
  auto *controller = new csci3081::Controller(argc, argv);

  // The controller will call Run of the viewer
  controller->Run();
  return 0;
}
