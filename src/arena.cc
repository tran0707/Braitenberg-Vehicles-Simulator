/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include "src/braitenberg_vehicle.h"
#include "src/arena.h"
#include "src/light.h"
#include "src/factory.h"
#include "src/derived_factory.h"
#include "src/light_decorator.h"
#include "src/food_decorator.h"
#include "src/bv_decorator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

Arena::Arena(): x_dim_(X_DIM),
      y_dim_(Y_DIM),
      entities_(),
      mobile_entities_(),
      predator_container_1(nullptr),
      predator_container_2(nullptr),
      predator_entity(nullptr),
      iteration_count_(0),
      random_entities(), is_deco_food(false),
      is_deco_light(false), is_deco_bv(false),
      is_dead_pre(false), ready_to_deco(false),
      index_saved_ent2(0), current_pose(Pose(0, 0)) {
    AddEntity(new Light());
    AddEntity(new Food());
    AddEntity(new BraitenbergVehicle());
}

Arena::Arena(json_object* object, bool csv_ext, bool json_ext,
double json_x_dim, double json_y_dim): x_dim_(X_DIM),
      y_dim_(Y_DIM),
      entities_(),
      mobile_entities_(),
      predator_container_1(nullptr),
      predator_container_2(nullptr),
      predator_entity(nullptr),
      iteration_count_(0),
      random_entities(), is_deco_food(false),
      is_deco_light(false), is_deco_bv(false),
      is_dead_pre(false), ready_to_deco(false),
      index_saved_ent2(0), current_pose(Pose(0, 0)) {
  json_object arena_object = *object;
  if (csv_ext == false && json_ext == true) {
    x_dim_ = json_x_dim;
    y_dim_ = json_y_dim;
  } else {
    x_dim_ = arena_object["width"].get<double>();
    y_dim_ = arena_object["height"].get<double>();
  }
  json_array& entities = arena_object["entities"].get<json_array>();
  for (unsigned int f = 0; f < entities.size(); f++) {
    json_object& entity_config = entities[f].get<json_object>();
    json_object *config = &entity_config;
    EntityType etype = get_entity_type(
      entity_config["type"].get<std::string>());

    Light *light_entity = NULL;
    Food *food_entity = NULL;
    BraitenbergVehicle *vehicle_entity = NULL;
    // Predator
    predator_entity = NULL;
    switch (etype) {
      case (kLight):
      {
         LightFactory *l_enti = new LightFactory();
         light_entity = l_enti->LightFactory::Create(config);
        break;
      }
      case (kFood):
      {
        FoodFactory *f_enti = new FoodFactory();
        food_entity = f_enti->FoodFactory::Create(config);
        break;
      }
      case (kBraitenberg):
      {
        VehicleFactory *v_enti = new VehicleFactory();
        vehicle_entity = v_enti->VehicleFactory::Create(config);
        break;
      }
      case (kPredator):
      {
        PredatorFactory *p_enti = new PredatorFactory();
        predator_entity = p_enti->PredatorFactory::Create(config);
        break;
      }
      default:
      {
        std::cout << "FATAL: Bad entity type on creation" << std::endl;
        assert(false);
      }
    }
    if (predator_entity) {
      AddEntity(predator_entity);
    }
    if (light_entity) {
      AddEntity(light_entity);
    }
    if (food_entity) {
      AddEntity(food_entity);
    }
    if (vehicle_entity) {
      AddEntity(vehicle_entity);
    }
  }
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Arena::AddEntity(ArenaEntity* ent) {
  entities_.push_back(ent);
  if (ent->is_mobile()) {
    auto mob_ent = static_cast<ArenaMobileEntity*>(ent);
    mobile_entities_.push_back(mob_ent);
  }

  BraitenbergVehicle* bv = dynamic_cast<BraitenbergVehicle*>(ent);
  if (bv) {
    bv->UpdateLightSensors();
  }
}

void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

// function to random choose identity
int Arena::rand_identity(std::vector<EntityType> identity) {
  unsigned int seed = time(NULL);
  int index = rand_r(&seed) % identity.size();
  return index;
}

void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   * Should this be just the mobile entities ??
   *  ^^ Nope, I use TimestepUpdate on all entities now (to update sensors)
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }

   /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  EntityType which_entity;
  int where = 0;
  int index_ent1 = 0;
  int index_ent2 = 0;
  for (auto &ent1 : mobile_entities_) {
    index_ent1++;
    /*********************Predator decorator******************/
    if (ent1->get_type() == kPredator
      || ent1->get_type() == kPredator_Deco_BV
      || ent1->get_type() == kPredator_Deco_Light
      || ent1->get_type() == kPredator_Deco_Food) {
      // saved the original address
      if (ent1->get_type() == kPredator) {
        predator_container_1 = static_cast<Predator*>(
          mobile_entities_[index_ent1-1]);
      }
      // clear and add in vector 3 entites
      if (iteration_count_ == 0) {
        random_entities.clear();
        random_entities.push_back(kPredator_Deco_Food);
        random_entities.push_back(kPredator_Deco_Light);
        random_entities.push_back(kPredator_Deco_BV);
      }
      iteration_count_++;

      if (iteration_count_ == 150
        || iteration_count_ == 300
        || iteration_count_ == 450) {
        // remove outter layer first before decorate with new layer
        if (ent1->get_type() != kPredator) {
          delete(mobile_entities_[index_ent1 -1]);
          mobile_entities_[index_ent1 -1] = predator_container_1;
          ent1 = mobile_entities_[index_ent1-1];
        }


        // choose random 1 in remain random_entities
        where = rand_identity(random_entities);
        which_entity = random_entities[where];
        random_entities.erase(random_entities.begin() + where);
        // decorate BV
        if (which_entity == kPredator_Deco_BV) {
          mobile_entities_[index_ent1-1] = new BraitenbergVehicle_Decorator(
            static_cast<Predator*>(mobile_entities_[index_ent1-1]));
          ent1 = mobile_entities_[index_ent1-1];
          is_deco_bv = true;
        // decorate Light
        } else if (which_entity == kPredator_Deco_Light) {
          mobile_entities_[index_ent1-1] = new Light_Decorator(
            static_cast<Predator*>(mobile_entities_[index_ent1-1]));
          ent1 = mobile_entities_[index_ent1-1];
          is_deco_light = true;
        // decorate Food
        } else if (which_entity == kPredator_Deco_Food) {
          mobile_entities_[index_ent1-1] =
          static_cast<ArenaMobileEntity*>(static_cast<ArenaEntity*>(
            (new Food_Decorator(static_cast<Predator*>(
              mobile_entities_[index_ent1-1])))));
          is_deco_food = true;
          ent1 = mobile_entities_[index_ent1-1];
        }
      ready_to_deco = true;
      }

      if (iteration_count_ == 600) {
      // Predator die => remove all layer before die
        current_pose = mobile_entities_[index_ent1-1]->get_pose();
        if (ent1->get_type() != kPredator) {
          delete(mobile_entities_[index_ent1-1]);
        }
        mobile_entities_[index_ent1-1] = predator_container_1;
        ent1 = mobile_entities_[index_ent1-1];
        is_dead_pre = true;
        ready_to_deco = true;
      }
    }

    // Collision with Wall
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
        ent1->HandleCollision(wall);
    }
    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */
    for (auto &ent2 : entities_) {
      if (static_cast<unsigned int>(index_ent2) == entities_.size()) {
        index_ent2 = 0;
      }
      index_ent2++;

      if (ready_to_deco) {
        if (ent2->get_type() == kPredator
          || ent2->get_type() == kPredator_Deco_BV
          || ent2->get_type() == kPredator_Deco_Light
          || ent2->get_type() == kPredator_Deco_Food
          || ent2->get_type() == kDeadPredator) {
        ready_to_deco = false;
        // saved the origin address
        if (ent2->get_type() == kPredator) {
          predator_container_2 = static_cast<Predator*>(
            entities_[index_ent2 -1]);
        }

        // decorate BV
        if (is_deco_bv) {
          current_pose = entities_[index_ent2 -1]->get_pose();
          entities_[index_ent2 -1] = mobile_entities_[index_ent1-1];
          entities_[index_ent2-1]->set_pose(current_pose);
          entities_[index_ent2-1]->set_radius(15);
          ent2 = entities_[index_ent2 -1];
          is_deco_bv = false;
        // decorate Light
        } else if (is_deco_light) {
          current_pose = entities_[index_ent2 -1]->get_pose();
          entities_[index_ent2 -1] = mobile_entities_[index_ent1-1];
          entities_[index_ent2-1]->set_pose(current_pose);
          ent2 = entities_[index_ent2 -1];
          index_saved_ent2 = index_ent2-1;
          is_deco_light = false;
        // decorate Food
        } else if (is_deco_food) {
          current_pose = entities_[index_ent2 -1]->get_pose();
          entities_[index_ent2 -1] = mobile_entities_[index_ent1-1];
          entities_[index_ent2-1]->set_pose(current_pose);
          ent2 = entities_[index_ent2 -1];
          ent2->set_mobility(false);
          static_cast<ArenaMobileEntity*>(ent2)->set_is_moving(false);
          is_deco_food = false;
        // killed Predator and turn it to ghost
        } else if (is_dead_pre) {
          entities_[index_ent2-1] = mobile_entities_[index_ent1-1];
          entities_[index_ent2 -1]->set_color(RgbColor(kGhost));
          entities_[index_ent2 -1]->set_type(kDeadPredator);
          entities_[index_ent2 -1]->set_mobility(false);
          entities_[index_ent2 -1]->set_pose(current_pose);
          static_cast<ArenaMobileEntity*>(
            entities_[index_ent2 -1])->set_is_moving(false);
          is_dead_pre = false;
          // break;
        }
      }
    }

      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        // if a braitenberg vehicle collides with food, call consume on bv
        // this is pretty ugly, I should move it into HandleCollision
        if (ent1->get_type() == kBraitenberg &&
            ent2->get_type() == kFood) {
          ent1->HandleCollision(ent2->get_type(), ent2);
          // ent1->LoadFromObject(config);
          // static_cast<BraitenbergVehicle*>(ent1)->ConsumeFood();
        } else if (ent1->get_type() == kFood &&
                   ent2->get_type() == kBraitenberg) {
          // static_cast<BraitenbergVehicle*>(ent2)->ConsumeFood();
        ent2->HandleCollision(ent1->get_type(), ent1);
        // ent1->LoadFromObject(config);
        }

        // case for Predator vs BraitenbergVehicle
        if (ent1->get_type() == kPredator
          && ent2->get_type() == kBraitenberg) {
          ent1->HandleCollision(ent2->get_type(), ent2);
        } else if (ent1->get_type() == kBraitenberg &&
        ent2->get_type() == kPredator) {
          ent2->HandleCollision(ent1->get_type(), ent1);
        }

        // case for kPredator_Deco_Food vs BraitenbergVehicle
        if (ent1->get_type() == kPredator_Deco_Food
          && ent2->get_type() == kBraitenberg) {
          ent1->HandleCollision(ent2->get_type(), ent2);
        } else if (ent1->get_type() == kBraitenberg
          && ent2->get_type() == kPredator_Deco_Food) {
          ent2->HandleCollision(ent1->get_type(), ent1);
        }

        // case for kPredator_Deco_Light vs BraitenbergVehicle
        if (ent1->get_type() == kPredator_Deco_Light
          && ent2->get_type() == kBraitenberg) {
          ent1->HandleCollision(ent2->get_type(), ent2);
        } else if (ent1->get_type() == kBraitenberg
          && ent2->get_type() == kPredator_Deco_Light) {
          ent2->HandleCollision(ent1->get_type(), ent1);
        }

        // case for kPredator_Deco_BV vs BraitenbergVehicle
        if (ent1->get_type() == kPredator_Deco_BV
          && ent2->get_type() == kBraitenberg) {
          ent1->HandleCollision(ent2->get_type(), ent2);
        } else if (ent1->get_type() == kBraitenberg
          && ent2->get_type() == kPredator_Deco_BV) {
          ent2->HandleCollision(ent1->get_type(), ent1);
        }

        // lights and braitenberg vehicles do not collide
        // nothing collides with food, but bv's call consume() if they do
        if ((ent2->get_type() == kBraitenberg && ent1->get_type() == kLight) ||
            (ent2->get_type() == kLight && ent1->get_type() == kBraitenberg) ||
            (ent2->get_type() == kFood) || (ent1->get_type() == kFood) ||
            (ent2->get_type() == kPredator && ent1->get_type() == kLight) ||
            (ent2->get_type() == kLight && ent1->get_type() == kPredator) ||
            (ent2->get_type() == kLight && ent1->get_type() == kLight) ||

            // when BV is dead => no Update and HandleCollision
            (ent2->get_type() == kDeadBV && ent1->get_type() == kLight) ||
            (ent2->get_type() == kLight && ent1->get_type() == kDeadBV) ||
            (ent2->get_type() == kDeadBV && ent1->get_type() == kPredator) ||
            (ent2->get_type() == kPredator && ent1->get_type() == kDeadBV) ||
            (ent2->get_type() == kDeadBV && ent1->get_type() == kFood) ||
            (ent2->get_type() == kFood && ent1->get_type() == kDeadBV) ||
            (ent2->get_type() == kDeadBV && ent1->get_type() == kBraitenberg) ||
            (ent2->get_type() == kBraitenberg && ent1->get_type() == kDeadBV) ||

            // for dead Predator
            (ent2->get_type() == kDeadPredator &&
             ent1->get_type() == kLight) ||
            (ent2->get_type() == kLight &&
              ent1->get_type() == kDeadPredator) ||
            (ent2->get_type() == kDeadPredator &&
             ent1->get_type() == kPredator) ||
            (ent2->get_type() == kPredator &&
             ent1->get_type() == kDeadPredator) ||
            (ent2->get_type() == kDeadPredator && ent1->get_type() == kFood) ||
            (ent2->get_type() == kFood &&
             ent1->get_type() == kDeadPredator) ||
            (ent2->get_type() == kDeadPredator &&
             ent1->get_type() == kBraitenberg) ||
            (ent2->get_type() == kBraitenberg &&
             ent1->get_type() == kDeadPredator) ||

            // for Deco vs BV
            (ent1->get_type() == kPredator &&
             ent2->get_type() == kBraitenberg) ||
            (ent1->get_type() == kBraitenberg &&
             ent2->get_type() == kPredator) ||
            (ent1->get_type() == kPredator_Deco_Food &&
             ent2->get_type() == kBraitenberg) ||
            (ent1->get_type() == kBraitenberg &&
             ent2->get_type() == kPredator_Deco_Food) ||
            (ent1->get_type() == kPredator_Deco_Light &&
             ent2->get_type() == kBraitenberg)||
            (ent1->get_type() == kBraitenberg &&
             ent2->get_type() == kPredator_Deco_Light) ||
            (ent1->get_type() == kPredator_Deco_BV &&
             ent2->get_type() == kBraitenberg) ||
            (ent1->get_type() == kBraitenberg &&
             ent2->get_type() == kPredator_Deco_BV) ||

            // for Deco vs Predator
            (ent1->get_type() == kPredator &&
             ent2->get_type() == kPredator_Deco_BV) ||
            (ent1->get_type() == kPredator_Deco_BV &&
             ent2->get_type() == kPredator) ||
            (ent1->get_type() == kPredator &&
             ent2->get_type() == kPredator_Deco_Light) ||
            (ent1->get_type() == kPredator_Deco_Light &&
             ent2->get_type() == kPredator) ||
            (ent1->get_type() == kPredator &&
             ent2->get_type() == kPredator_Deco_Food) ||
            (ent1->get_type() == kPredator_Deco_Food &&
             ent2->get_type() == kPredator) ||

            // for DeadBV vs Deco
            (ent1->get_type() == kDeadBV &&
             ent2->get_type() == kPredator_Deco_Food) ||
            (ent1->get_type() == kPredator_Deco_Food &&
             ent2->get_type() == kDeadBV) ||
            (ent1->get_type() == kDeadBV &&
             ent2->get_type() == kPredator_Deco_Light) ||
            (ent1->get_type() == kPredator_Deco_Light &&
             ent2->get_type() == kDeadBV) ||
            (ent1->get_type() == kDeadBV &&
             ent2->get_type() == kPredator_Deco_BV) ||
            (ent1->get_type() == kPredator_Deco_BV &&
             ent2->get_type() == kDeadBV) ||

            // for kDeadPredator vs Deco
            (ent1->get_type() == kDeadPredator &&
             ent2->get_type() == kPredator_Deco_Food) ||
            (ent1->get_type() == kPredator_Deco_Food &&
             ent2->get_type() == kDeadPredator) ||
            (ent1->get_type() == kDeadPredator &&
             ent2->get_type() == kPredator_Deco_Light) ||
            (ent1->get_type() == kPredator_Deco_Light &&
             ent2->get_type() == kDeadPredator) ||
            (ent1->get_type() == kDeadPredator &&
             ent2->get_type() == kPredator_Deco_BV) ||
            (ent1->get_type() == kPredator_Deco_BV &&
             ent2->get_type() == kDeadPredator) ||

            // for Light vs Deco_Light
            (ent1->get_type() == kPredator_Deco_Light &&
             ent2->get_type() == kLight) ||
            (ent1->get_type() == kLight &&
             ent2->get_type() == kPredator_Deco_Light) ||

            // for DeadBV vs kDeadPredator
            (ent1->get_type() == kDeadBV &&
              ent2->get_type() == kDeadPredator) ||
            (ent1->get_type() == kDeadPredator &&
              ent2->get_type() == kDeadBV)) {
          continue;
        }
        AdjustEntityOverlap(ent1, ent2);
          ent1->HandleCollision(ent2->get_type(), ent2);
      }
    }
    // for BV
    if (ent1->get_type() == kBraitenberg) {
      BraitenbergVehicle* bv = static_cast<BraitenbergVehicle*>(ent1);
      for (unsigned int f = 0; f < entities_.size(); f++) {
        bv->SenseEntity(*entities_[f]);
      }
      bv->Update();
    }

    // for predator
    if (ent1->get_type() == kPredator && iteration_count_ != 600) {
      if (ent1->is_collision_with_bv() == true) {
        iteration_count_ = 0;
      } else {
        Predator* pre_ent = static_cast<Predator*>(ent1);
        for (unsigned int f = 0; f < entities_.size(); f++) {
          pre_ent->SenseEntity(*entities_[f]);
        }
        pre_ent->Update();
      }
    }

    // for Predator Food Deco
    if (ent1->get_type() == kPredator_Deco_Food && iteration_count_ != 600) {
      if (ent1->is_collision_with_bv() == true) {
        iteration_count_ = 0;
        // un-decorate Food => back to Predator
        current_pose = entities_[index_saved_ent2]->get_pose();
        delete(entities_[index_saved_ent2]);
        entities_[index_saved_ent2] = predator_container_2;
        entities_[index_saved_ent2]->set_pose(current_pose);
        ent1 = static_cast<ArenaMobileEntity*>(entities_[index_saved_ent2]);
      }
    }

    // for Predator Light Deco
    if (ent1->get_type() == kPredator_Deco_Light && iteration_count_ != 600) {
      if (ent1->is_collision_with_bv() == true) {
        iteration_count_ = 0;
        // un-decorate Light => back to Predator
        current_pose = entities_[index_saved_ent2]->get_pose();
        delete(entities_[index_saved_ent2]);
        entities_[index_saved_ent2] = predator_container_2;
        entities_[index_saved_ent2]->set_pose(current_pose);
        ent1 = static_cast<ArenaMobileEntity*>(entities_[index_saved_ent2]);
      }
    }

    // for Predator BV Deco
    if (ent1->get_type() == kPredator_Deco_BV && iteration_count_ != 600) {
      if (ent1->is_collision_with_bv() == true) {
        iteration_count_ = 0;
        // un-decorate BV => back to Predator
        current_pose = entities_[index_saved_ent2]->get_pose();
        delete(entities_[index_saved_ent2]);
        entities_[index_saved_ent2] = predator_container_2;
        entities_[index_saved_ent2]->set_pose(current_pose);
        ent1 = static_cast<ArenaMobileEntity*>(entities_[index_saved_ent2]);
      } else {
        BraitenbergVehicle_Decorator* pre_ent =
        static_cast<BraitenbergVehicle_Decorator*>(ent1);
        for (unsigned int f = 0; f < entities_.size(); f++) {
          pre_ent->SenseEntity(*entities_[f]);
        }
        pre_ent->Update();
      }
    }
  }
}  // UpdateEntitiesTimestep()

// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
/* @TODO: Add to Pose distance distance_between (e.g. overload operator -)
*/
/* @BUG: The robot will pass through the home food on occasion. The problem
 * is likely due to the adjustment being in the wrong direction. This could
 * be because the cos/sin generate the wrong sign of the distance_to_move
 * when the collision is in a specific quadrant relative to the center of the
 * colliding entities..
 */
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between;
    double angle = atan2(delta_y, delta_x);

    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
