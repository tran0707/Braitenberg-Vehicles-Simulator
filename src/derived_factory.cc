/**
 * @file derived_factory.cc
 *
 * @copyright 2019 tran0707 , All rights reserved.
 */
#include "src/derived_factory.h"
#include "src/factory.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

FoodFactory::FoodFactory() {}
FoodFactory::~FoodFactory() {}

Food *FoodFactory::Create(__unused json_object* food_config) {
Food *new_food = new Food();
new_food->LoadFromObject(food_config);
return new_food;
}


LightFactory::LightFactory() {}
LightFactory::~LightFactory() {
}


Light *LightFactory::Create(__unused json_object* light_config) {
Light *new_light = new Light();
new_light->LoadFromObject(light_config);
return new_light;
}

VehicleFactory::VehicleFactory() {}
VehicleFactory::~VehicleFactory() {}

BraitenbergVehicle *VehicleFactory::Create(__unused json_object* v_config) {
BraitenbergVehicle *new_vehicle = new BraitenbergVehicle();
new_vehicle->BraitenbergVehicle::LoadFromObject(v_config);
return new_vehicle;
}

PredatorFactory::PredatorFactory() {}
PredatorFactory::~PredatorFactory() {}

Predator *PredatorFactory::Create(__unused json_object* p_config) {
Predator *new_predator = new Predator();
new_predator->Predator::LoadFromObject(p_config);
return new_predator;
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
