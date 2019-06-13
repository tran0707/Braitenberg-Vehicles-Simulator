/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/rgb_color.h"
#include "src/predator.h"
#include "src/observer.h"
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
GraphicsArenaViewer::GraphicsArenaViewer(
    int width, int height,
    Controller * controller) :
    GraphicsApp(
        width + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        height,
        "Robot Simulation"),
    controller_(controller),
    arena_(nullptr),
    xOffset_(0),
    nanogui_intialized_(false),
    gui(nullptr),  window(),
    GAV_obs_(),
    text_l_container_(), text_f_container_(), text_bv_container_(),
    BV(), GAV_f_vel_(), GAV_l_vel_(), GAV_bv_vel_() {
      xOffset_ = GUI_MENU_WIDTH + GUI_MENU_GAP;
      GAV_l_vel_ = WheelVelocity(0, 0);
      GAV_f_vel_ = WheelVelocity(0, 0);
      GAV_bv_vel_ = WheelVelocity(0, 0);
      GAV_obs_ = new Observer();
      GAV_obs_->Data_Setter(&text_l_container_, &text_f_container_,
        &text_bv_container_);
}

void GraphicsArenaViewer::InitNanoGUI() {
    if (!nanogui_intialized_) {
      gui = new nanogui::FormHelper(screen());
    } else {
      window->dispose();
    }

    window =
          gui->addWindow(
              // Eigen::Vector2i(window_width()
              // - GUI_MENU_WIDTH - GUI_MENU_GAP * 2, 0),
              Eigen::Vector2i(0, 0),
              "Menu");
    window->setFixedWidth(GUI_MENU_WIDTH);
    window->setLayout(new nanogui::GroupLayout());

    // Creating a panel impacts the layout. Widgets, sliders, buttons can be
    // assigned to either the window or the panel.

    nanogui::Widget *panel = new nanogui::Widget(window);
    panel->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 0));
    // *************** Add GUI ************************//

    AddEntityPanel(window);

    panel = new nanogui::Widget(window);
    panel->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 0));
    // Lays out all the components with "15" units of inbetween spacing
    // panel->setLayout(new nanogui::BoxLayout(
    //  nanogui::Orientation::Vertical,nanogui::Alignment::Middle, 0, 15));

    new nanogui::Label(window, "Game Control", "sans-bold");
    playing_button_ =
      gui->addButton(
        "Play",
        std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
    reset_button_ =
      gui->addButton(
        "Reset",
        std::bind(&GraphicsArenaViewer::OnResetButtonPressed, this));
    screen()->performLayout();

    nanogui_intialized_ = true;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    controller_->AdvanceTime(dt);
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  if (!paused_) {
    playing_button_->setCaption("Play");
    paused_ = true;
  } else {
    playing_button_->setCaption("Pause");
    paused_ = false;
  }
}

void GraphicsArenaViewer::OnResetButtonPressed() {
  paused_ = true;
  playing_button_->setCaption("Play");
  controller_->Reset();
}

void GraphicsArenaViewer::SetArena(Arena *arena) {
  arena_ = arena;
  if (nanogui_intialized_) {
    InitNanoGUI();
  }
}


/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, xOffset_, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  nvgBeginPath(ctx);
  float x = static_cast<float>(entity->get_pose().x);
  float y = static_cast<float>(entity->get_pose().y);
  float rad = static_cast<float>(entity->get_radius());
  // draw food with a radius of 5 less than actual radius. BraitenbergVehicles
  // will 'eat' when withing 5 radius of the food
  if (entity->get_type() == kFood
    || entity->get_type() == kPredator_Deco_Food) {
    rad -= 5;
  }
  // draw circle for all entities
  nvgCircle(ctx, xOffset_ + x, y, rad);
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);
  nvgSave(ctx);
  // draw the sensors if the entity is a BraitenbergVehicle
  // the nvg calls are porobably not perfect, but we haven't been taught them
  /************************* DRAWING SENSORS *********************************/
  if (entity->get_type() == kBraitenberg) {
    auto bv = static_cast<const BraitenbergVehicle * const>(entity);
    std::vector<Pose> sensors = bv->get_light_sensors_const();
    Pose left_sens_pose = sensors[0];
    Pose right_sens_pose = sensors[1];
    // left sensor drawing save the ctx twice, once for the circle and
    // once for the text
    nvgSave(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(left_sens_pose.x),
            static_cast<float>(left_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    // right sensor drawing
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(right_sens_pose.x),
            static_cast<float>(right_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  }

  // for kPredator
  if (entity->get_type() == kPredator) {
    auto bv = static_cast<const Predator * const>(entity);
    std::vector<Pose> sensors = bv->get_light_sensors_const();
    Pose left_sens_pose = sensors[0];
    Pose right_sens_pose = sensors[1];
    // left sensor drawing save the ctx twice, once for the circle and
    // once for the text
    nvgSave(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(left_sens_pose.x),
            static_cast<float>(left_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    // right sensor drawing
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(right_sens_pose.x),
            static_cast<float>(right_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  }

  // for kDeadBV
  if (entity->get_type() == kDeadBV) {
    auto bv = static_cast<const BraitenbergVehicle * const>(entity);
    std::vector<Pose> sensors = bv->get_light_sensors_const();
    Pose left_sens_pose = sensors[0];
    Pose right_sens_pose = sensors[1];
    // left sensor drawing save the ctx twice, once for the circle and
    // once for the text
    nvgSave(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(left_sens_pose.x),
            static_cast<float>(left_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    // right sensor drawing
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(right_sens_pose.x),
            static_cast<float>(right_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  }

  // kDeadPredator
  if (entity->get_type() ==kDeadPredator) {
    auto bv = static_cast<const Predator * const>(entity);
    std::vector<Pose> sensors = bv->get_light_sensors_const();
    Pose left_sens_pose = sensors[0];
    Pose right_sens_pose = sensors[1];
    // left sensor drawing save the ctx twice, once for the circle and
    // once for the text
    nvgSave(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(left_sens_pose.x),
            static_cast<float>(left_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    // right sensor drawing
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(right_sens_pose.x),
            static_cast<float>(right_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  }

  // kPredator_Deco_BV
  if (entity->get_type() == kPredator_Deco_BV) {
    auto bv = static_cast<const BraitenbergVehicle_Decorator * const>(entity);
    std::vector<Pose> sensors = bv->get_light_sensors_const();
    Pose left_sens_pose = sensors[0];
    Pose right_sens_pose = sensors[1];
    // left sensor drawing save the ctx twice, once for the circle and
    // once for the text
    nvgSave(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(left_sens_pose.x),
            static_cast<float>(left_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgSave(ctx);
    nvgBeginPath(ctx);
    // right sensor drawing
    nvgCircle(ctx,
            xOffset_ + static_cast<float>(right_sens_pose.x),
            static_cast<float>(right_sens_pose.y),
            static_cast<float>(SENSOR_LIGHT_RAD));
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  }

  /*********************** END DRAWING SENSORS *******************************/
  nvgRestore(ctx);
  // light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  std::string name;
    name = entity->get_name();
  nvgText(ctx,
          xOffset_ + static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          name.c_str(), nullptr);
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  /*if (game_won_) {
    nvgTextBox(ctx, xOffset_ + 300, 300, 500, "WINNER", NULL);
  } else if (game_lost_) {
    nvgTextBox(ctx, xOffset_ + 300, 300, 500, "GAME OVER", NULL);
  }*/
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
  // DrawRobot(ctx, arena_->robot());
}

void GraphicsArenaViewer::AddEntityPanel(nanogui::Widget * panel) {
  if (arena_->get_entities().size() == 0) {
    return;
  }

  ArenaEntity* defaultEntity = arena_->get_entities()[0];

  new nanogui::Label(panel, "Entity", "sans-bold");
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  std::vector<std::string> entityNames;
  int total_count = 0;
  for (auto &entity : entities) {
    entityNames.push_back(entity->get_name());
    if (entity->get_type() == kBraitenberg) {
      total_count++;
    }
  }
  nanogui::ComboBox* entitySelect = new nanogui::ComboBox(panel, entityNames);
  entitySelect->setFixedWidth(COMBO_BOX_WIDTH);


  nanogui::CheckBox* isMobile = new nanogui::CheckBox(panel, "Mobile");
  isMobile->setChecked(defaultEntity->is_mobile());
  isMobile->setVisible(defaultEntity->is_mobile());

  std::vector<std::string> behaviorNames;
  behaviorNames.push_back("Default");
  behaviorNames.push_back("Aggressive");
  behaviorNames.push_back("Coward");
  behaviorNames.push_back("Explore");
  behaviorNames.push_back("Love");

  std::vector<nanogui::Widget*> robotWidgets;

  robotWidgets.push_back(new nanogui::Label(
    panel, "Light Behavior", "sans-bold"));
  nanogui::Widget * robotPanel = new nanogui::Widget(panel);
  robotWidgets.push_back(robotPanel);
  robotPanel->setLayout(new nanogui::BoxLayout(
    nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 0, 0));
  nanogui::ComboBox* lightBehaviorSelect =
    new nanogui::ComboBox(robotPanel, behaviorNames);
  lightBehaviorSelect->setFixedWidth(COMBO_BOX_WIDTH -10);
  nanogui::Widget *space = new nanogui::Widget(robotPanel);
  nanogui::Widget * sliderPanel = new nanogui::Widget(robotPanel);
  space->setFixedHeight(10);
  sliderPanel->setLayout(
    new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 0));
  nanogui::Widget *lbl = new nanogui::Label(
    sliderPanel, "Intensity", "sans-bold");
  lbl->setFixedWidth(50);
  nanogui::Slider *slider = new nanogui::Slider(sliderPanel);
  slider->setFixedWidth(90);
  space->setVisible(false);
  sliderPanel->setVisible(false);

  robotWidgets.push_back(new nanogui::Label(
    panel, "Food Behavior", "sans-bold"));
  robotPanel = new nanogui::Widget(panel);
  robotWidgets.push_back(robotPanel);
  robotPanel->setLayout(new nanogui::BoxLayout(
    nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 0, 0));
  nanogui::ComboBox* foodBehaviorSelect = new nanogui::ComboBox(
    robotPanel, behaviorNames);
  foodBehaviorSelect->setFixedWidth(COMBO_BOX_WIDTH -10);
  space = new nanogui::Widget(robotPanel);
  sliderPanel = new nanogui::Widget(robotPanel);
  space->setFixedHeight(10);
  sliderPanel->setLayout(
    new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 0));
  lbl = new nanogui::Label(sliderPanel, "Intensity", "sans-bold");
  lbl->setFixedWidth(50);
  slider = new nanogui::Slider(sliderPanel);
  slider->setFixedWidth(90);
  space->setVisible(false);
  sliderPanel->setVisible(false);

  // added button for BV Behavior
  robotWidgets.push_back(new nanogui::Label(
    panel, "BV Behavior", "sans-bold"));
  robotPanel = new nanogui::Widget(panel);
  robotWidgets.push_back(robotPanel);
  robotPanel->setLayout(new nanogui::BoxLayout(
    nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 0, 0));
  nanogui::ComboBox*bvBehaviorSelect = new nanogui::ComboBox(
    robotPanel, behaviorNames);
  bvBehaviorSelect->setFixedWidth(COMBO_BOX_WIDTH -10);
  space = new nanogui::Widget(robotPanel);
  sliderPanel = new nanogui::Widget(robotPanel);
  space->setFixedHeight(10);
  sliderPanel->setLayout(
    new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 0));
  lbl = new nanogui::Label(sliderPanel, "Intensity", "sans-bold");
  lbl->setFixedWidth(50);
  slider = new nanogui::Slider(sliderPanel);
  slider->setFixedWidth(90);
  space->setVisible(false);
  sliderPanel->setVisible(false);

  for (unsigned int f = 0; f < robotWidgets.size(); f++) {
    robotWidgets[f]->setVisible(defaultEntity->get_type() == kBraitenberg);
  }

  if (defaultEntity->get_type() == kBraitenberg) {
    lightBehaviorSelect->setSelectedIndex(
      static_cast<BraitenbergVehicle*>(defaultEntity)->get_light_behavior());
    foodBehaviorSelect->setSelectedIndex(
      static_cast<BraitenbergVehicle*>(defaultEntity)->get_food_behavior());
    // added for bv
    bvBehaviorSelect->setSelectedIndex(
      static_cast<BraitenbergVehicle*>(defaultEntity)->get_bv_behavior());

    // observer pattern subscribe for the default BV
    BV = static_cast<BraitenbergVehicle*>(defaultEntity);
    BV->Subscribe(GAV_obs_);
    BV->subscribe_checker = true;
  }
  // observer pattern start here
  // ******* Create the Wheel Velocity Grid  ******** //
  robotWidgets.push_back(new nanogui::Label(
    panel, "Wheel Velocities", "sans-bold"));
  nanogui::Widget* grid = new nanogui::Widget(panel);
  // A grid with 3 columns
  grid->setLayout(
  new nanogui::GridLayout(nanogui::Orientation::Horizontal, 3,
  nanogui::Alignment::Middle, /*int margin = */0, /*int spacing = */0));
  robotWidgets.push_back(grid);

  // Columns Headers Row
  new nanogui::Label(grid, "", "sans-bold");
  new nanogui::Label(grid, "Left", "sans-bold");
  new nanogui::Label(grid, "Right", "sans-bold");

  // Next Row for wheel velocities from light behavior
  new nanogui::Label(grid, "Light", "sans-bold");
  nanogui::TextBox* light_value_left_ = new nanogui::TextBox(grid, "0.0");
  light_value_left_->setFixedWidth(55);
  nanogui::TextBox* light_value_right_ = new nanogui::TextBox(grid, "0.0");
  light_value_right_->setFixedWidth(55);

  text_l_container_.left = light_value_left_;
  text_l_container_.right = light_value_right_;

  new nanogui::Label(grid, "Food", "sans-bold");
  nanogui::TextBox* food_value_left_ = new nanogui::TextBox(grid, "0.0");
  food_value_left_->setFixedWidth(55);
  nanogui::TextBox* food_value_right_ = new nanogui::TextBox(grid, "0.0");
  food_value_right_->setFixedWidth(55);

  text_f_container_.left = food_value_left_;
  text_f_container_.right = food_value_right_;

  new nanogui::Label(grid, "BV", "sans-bold");
  nanogui::TextBox* bv_value_left_ = new nanogui::TextBox(grid, "0.0");
  bv_value_left_->setFixedWidth(55);
  nanogui::TextBox* bv_value_right_ = new nanogui::TextBox(grid, "0.0");
  bv_value_right_->setFixedWidth(55);

  text_bv_container_.left = bv_value_left_;
  text_bv_container_.right = bv_value_right_;

  entitySelect->setCallback(
    [this, isMobile, robotWidgets, lightBehaviorSelect,
    foodBehaviorSelect/*added bv*/, bvBehaviorSelect, total_count](int index) {
      ArenaEntity* entity = this->arena_->get_entities()[index];
      if (entity->is_mobile()) {
        ArenaMobileEntity* mobileEntity =
        static_cast<ArenaMobileEntity*>(entity);
        isMobile->setChecked(mobileEntity->is_moving());
      }

      isMobile->setVisible(entity->is_mobile());

      for (unsigned int f = 0; f < robotWidgets.size(); f++) {
        robotWidgets[f]->setVisible(entity->get_type() == kBraitenberg);
      }

      if (entity->get_type() == kBraitenberg) {
        lightBehaviorSelect->setSelectedIndex(
          static_cast<BraitenbergVehicle*>(entity)->get_light_behavior());
        foodBehaviorSelect->setSelectedIndex(
          static_cast<BraitenbergVehicle*>(entity)->get_food_behavior());
        // added for bv
        bvBehaviorSelect->setSelectedIndex(
          static_cast<BraitenbergVehicle*>(entity)->get_bv_behavior());
      }

      // Observer Pattern Subscribe if not default
      if (entity->get_type() == kBraitenberg && total_count != 1) {
        BraitenbergVehicle * this_bv = static_cast<BraitenbergVehicle*>(entity);
        if (BV->subscribe_checker == true) {
          BV->Unsubscribe();
          BV->subscribe_checker = false;
        }
        this_bv->Subscribe(GAV_obs_);
        this_bv->subscribe_checker = true;
        BV = this_bv;
      }

      screen()->performLayout();
    });

  lightBehaviorSelect->setCallback(
    [this, entitySelect](int index) {
      ArenaEntity* entity =
      this->arena_->get_entities()[entitySelect->selectedIndex()];
      if (entity->get_type() == kBraitenberg) {
        static_cast<BraitenbergVehicle*>(entity)->set_light_behavior(
          static_cast<Behavior>(index));
      }
    });

  foodBehaviorSelect->setCallback(
    [this, entitySelect](int index) {
      ArenaEntity* entity =
      this->arena_->get_entities()[entitySelect->selectedIndex()];
      if (entity->get_type() == kBraitenberg) {
        static_cast<BraitenbergVehicle*>(entity)->set_food_behavior(
          static_cast<Behavior>(index));
      }
    });

  // added for bv
  bvBehaviorSelect->setCallback(
    [this, entitySelect](int index) {
      ArenaEntity* entity =
      this->arena_->get_entities()[entitySelect->selectedIndex()];
      if (entity->get_type() == kBraitenberg) {
        static_cast<BraitenbergVehicle*>(entity)->set_bv_behavior(
          static_cast<Behavior>(index));
      }
    });

  isMobile->setCallback(
    [this, entitySelect](bool moving) {
      ArenaEntity* entity =
      this->arena_->get_entities()[entitySelect->selectedIndex()];
      ArenaMobileEntity* mobileEntity = static_cast<ArenaMobileEntity*>(entity);
      mobileEntity->set_is_moving(moving);
    });
}

bool GraphicsArenaViewer::RunViewer() {
  return Run();
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
