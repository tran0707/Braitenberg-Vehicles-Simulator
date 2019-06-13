/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

int Light::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() :
    motion_behavior_(this) {
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_POSITION);
  set_radius(LIGHT_RADIUS);
  set_type(kLight);
  set_speed(3);

  // Set ID
  count++;
  set_id(count);
}

void Light::HandleCollision(__unused EntityType ent_type,
                               __unused ArenaEntity * object) {
  // set_heading(random_num<float>(0, 360));
  set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
}

void Light::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
      Pose pose = get_pose();

      // Movement is always along the heading_angle (i.e. the hypotenuse)
      double new_x =
        pose.x + std::cos(pose.theta * M_PI / 180.0) * get_speed() * dt;
      double new_y =
        pose.y + std::sin(pose.theta * M_PI / 180.0) * get_speed() * dt;

      /* Heading angle remaings the same */
      pose.x = new_x;
      pose.y = new_y;
      set_pose(pose);
  }

  Update();
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
