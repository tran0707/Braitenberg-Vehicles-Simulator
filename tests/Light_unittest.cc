/**
 * @file Light_unittest.cc
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
class LightTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    factory = new csci3081::LightFactory();
    std::string json = "{\"type\": \"Light\", \"x\":100, \"y\":250, \"r\":30 }";
    json_value * config = new json_value();
    std::string err = parse_json(config, json);
    new_light = factory->Create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }
  csci3081::LightFactory * factory;
  csci3081::Light * new_light;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(LightTest, LightCreateTest) {
  EXPECT_EQ(new_light->count, 1)
  << "FAIL: Wrong number of Light";
}

TEST_F(LightTest, LightGetterTest) {
    EXPECT_EQ(new_light->get_type(), kLight)
    << "FAIL: Wrong entity_type";
    EXPECT_EQ(new_light->is_mobile(), true)
    << "FAIL: Wrong is_mobile";

    EXPECT_EQ(new_light->get_radius(), 30)
    << "FAIL: Wrong Initial Radius";
    EXPECT_EQ(new_light->get_pose().x, 100)
    << "FAIL: Wrong Position.X";
    EXPECT_EQ(new_light->get_pose().y, 250)
    << "FAIL: Wrong Position.Y";

    EXPECT_EQ(new_light->get_color(), RgbColor(kWhite))
    << "FAIL: Wrong Vehicle Color";
}

TEST_F(LightTest, LightSetterTest) {
  EntityType light_type = kLight;
  new_light->set_type(light_type);
  EXPECT_EQ(new_light->get_type(), kLight)
  << "SETTER_FAIL: Wrong entity_type";

  new_light->set_id(1000);
  EXPECT_EQ(new_light->get_id(), 1000)
  << "SETTER_FAIL: Wrong Vehicle Entity id";

  new_light->set_mobility(true);
  EXPECT_EQ(new_light->is_mobile(), true)
  << "SETTER_FAIL: Wrong is_mobile";

  new_light->set_radius(10000.0);
  EXPECT_EQ(new_light->get_radius(), 10000.0)
  << "SETTER_FAIL: Wrong Initial Radius";

  Pose new_pose(500, 500, 180);
  new_light->set_pose(new_pose);
  EXPECT_EQ(new_light->get_pose().x, 500)
  << "SETTER_FAIL: Wrong Position.X";
  EXPECT_EQ(new_light->get_pose().y, 500)
  << "SETTER_FAIL: Wrong Position.Y";
  EXPECT_EQ(new_light->get_pose().theta, 180)
  << "SETTER_FAIL: Wrong Position.THETA";

  new_light->set_color(RgbColor(kBlue));
  EXPECT_EQ(new_light->get_color(), RgbColor(kBlue))
  << "FAIL: Wrong Vehicle Color";

  new_light->set_speed(100.0);
  EXPECT_EQ(new_light->get_speed(), 100.0)
  << "FAIL: Wrong speed";
}

NAMESPACE_END(csci3081);
