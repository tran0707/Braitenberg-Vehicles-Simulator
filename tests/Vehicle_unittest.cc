/**
 * @file Vehicle_unittest.cc
 *
 * @copyright 2019 tran0707 , All rights reserved.
 */

#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/factory.h"
#include "src/derived_factory.h"
#include "src/light.h"
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/rgb_color.h"
NAMESPACE_BEGIN(csci3081);

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class VehicleTest : public ::testing::Test {
 protected:
  virtual void SetUp() {  // setting up the variables in line 33 and 34
    factory = new csci3081::VehicleFactory();
    std::string json =
    " {\"type\": \"Braitenberg\", \"x\":270, \"y\":270, \"r\":15, \"theta\":"
    "215,\"light_behavior\": \"None\", \"food_behavior\": \"Explore\" }";
    json_value * config = new json_value();
    std::string err = parse_json(config, json);
    new_vehicle = factory->Create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }
csci3081::VehicleFactory * factory;
BraitenbergVehicle *new_vehicle;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(VehicleTest, BVCreateTest) {
  EXPECT_EQ(new_vehicle->count, 1)
  << "FAIL: Wrong number of vehicle";
}

TEST_F(VehicleTest, BVCreateGetterTest) {
    EXPECT_EQ(new_vehicle->get_type(), kBraitenberg)
     << "FAIL: Wrong entity_type";
    EXPECT_EQ(new_vehicle->is_mobile(), true)
    << "FAIL: Wrong is_mobile";
    EXPECT_EQ(new_vehicle->get_radius(), 15)
    << "FAIL: Wrong Initial Radius";

    EXPECT_EQ(new_vehicle->get_pose().x, 270)
    << "FAIL: Wrong Position.X";
    EXPECT_EQ(new_vehicle->get_pose().y, 270)
    << "FAIL: Wrong Position.Y";
    EXPECT_EQ(new_vehicle->get_pose().theta, 215)
    << "FAIL: Wrong Position.THETA";

    EXPECT_EQ(new_vehicle->get_color(), RgbColor(kMaroon))
    << "FAIL: Wrong Vehicle Color";

    EXPECT_EQ(new_vehicle->get_food_behavior(), kExplore)
    << "FAIL: Wrong food behavior";
    EXPECT_EQ(new_vehicle->get_light_behavior(), kNone)
    << "FAIL: Wrong light behavior";
}

TEST_F(VehicleTest, BVsetter_test) {
    EntityType vehicle_type = kBraitenberg;
    new_vehicle->set_type(vehicle_type);
    EXPECT_EQ(new_vehicle->get_type(), kBraitenberg)
    << "SETTER_FAIL: Wrong entity_type";

    new_vehicle->set_id(1000);
    EXPECT_EQ(new_vehicle->get_id(), 1000)
    << "SETTER_FAIL: Wrong Vehicle Entity id";

    new_vehicle->set_mobility(false);
    EXPECT_EQ(new_vehicle->is_mobile(), false)
    << "SETTER_FAIL: Wrong is_mobile";

    new_vehicle->set_radius(10000.0);
    EXPECT_EQ(new_vehicle->get_radius(), 10000.0)
    << "SETTER_FAIL: Wrong Initial Radius";

    Pose new_pose(500, 500, 180);
    new_vehicle->set_pose(new_pose);
    EXPECT_EQ(new_vehicle->get_pose().x, 500)
    << "SETTER_FAIL: Wrong Position.X";
    EXPECT_EQ(new_vehicle->get_pose().y, 500)
    << "SETTER_FAIL: Wrong Position.Y";
    EXPECT_EQ(new_vehicle->get_pose().theta, 180)
    << "SETTER_FAIL: Wrong Position.THETA";

    new_vehicle->set_food_behavior(kLove);
    new_vehicle->set_light_behavior(kNone);
    EXPECT_EQ(new_vehicle->get_food_behavior(), kLove)
    << "FAIL: Wrong food behavior";
    EXPECT_EQ(new_vehicle->get_light_behavior(), kNone)
    << "FAIL: Wrong light behavior";

    new_vehicle->set_color(RgbColor(kGold));
    EXPECT_EQ(new_vehicle->get_color(), RgbColor(kGold))
    << "FAIL: Wrong Vehicle Color";
}

NAMESPACE_END(csci3081);
