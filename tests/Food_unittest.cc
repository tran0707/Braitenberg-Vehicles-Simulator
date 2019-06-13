/**
 * @file Food_unittest.cc
 *
 * @copyright 2019 tran0707 , All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/factory.h"
#include "src/derived_factory.h"
#include "src/light.h"
NAMESPACE_BEGIN(csci3081);

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FoodTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    factory = new csci3081::FoodFactory();
    std::string json =
    " {\"type\": \"Food\", \"x\":500,\"y\":100, \"r\":20, \"theta\": 0.0 }";
    json_value * config = new json_value();
    std::string err = parse_json(config, json);
    new_food = factory->Create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }
  csci3081::FoodFactory * factory;
  csci3081::Food * new_food;
};
/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(FoodTest, FoodCreateTest) {
  EXPECT_EQ(new_food->count, 1)
  << "FAIL: Wrong number of Food";
}

TEST_F(FoodTest, FoodGetterTest) {
  EXPECT_EQ(new_food->get_type(), kFood)
  << "FAIL: Wrong entity_type";
  EXPECT_EQ(new_food->is_mobile(), false)
  << "FAIL: Wrong is_mobile";

  EXPECT_EQ(new_food->get_radius(), 20)
  << "FAIL: Wrong Initial Radius";
  EXPECT_EQ(new_food->get_pose().x, 500)
  << "FAIL: Wrong Position.X";
  EXPECT_EQ(new_food->get_pose().y, 100)
  << "FAIL: Wrong Position.Y";

  EXPECT_EQ(new_food->get_color(), RgbColor(kGreen))
  << "FAIL: Wrong Vehicle Color";
}

TEST_F(FoodTest, FoodSetterTest) {
  EntityType food_type = kFood;
  new_food->set_type(food_type);
  EXPECT_EQ(new_food->get_type(), kFood)
  << "SETTER_FAIL: Wrong entity_type";

  new_food->set_id(1000);
  EXPECT_EQ(new_food->get_id(), 1000)
  << "SETTER_FAIL: Wrong Vehicle Entity id";

  new_food->set_mobility(true);
  EXPECT_EQ(new_food->is_mobile(), true)
  << "SETTER_FAIL: Wrong is_mobile";

  new_food->set_radius(10000.0);
  EXPECT_EQ(new_food->get_radius(), 10000.0)
  << "SETTER_FAIL: Wrong Initial Radius";

  Pose new_pose(500, 500, 180);
  new_food->set_pose(new_pose);
  EXPECT_EQ(new_food->get_pose().x, 500)
  << "SETTER_FAIL: Wrong Position.X";
  EXPECT_EQ(new_food->get_pose().y, 500)
  << "SETTER_FAIL: Wrong Position.Y";
  EXPECT_EQ(new_food->get_pose().theta, 180)
  << "SETTER_FAIL: Wrong Position.THETA";

  new_food->set_color(RgbColor(kBlue));
  EXPECT_EQ(new_food->get_color(), RgbColor(kBlue))
  << "FAIL: Wrong Vehicle Color";
}

NAMESPACE_END(csci3081);
