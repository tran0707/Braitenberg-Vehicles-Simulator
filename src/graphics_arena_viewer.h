/**
 * @file graphics_arena_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_GRAPHICS_ARENA_VIEWER_H_
#define SRC_GRAPHICS_ARENA_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MinGfx-1.0/mingfx.h>

#include "src/arena.h"
#include "src/controller.h"
#include "src/common.h"
#include "src/wheel_velocity.h"
#include "src/data_box.h"
#include "src/braitenberg_vehicle.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

class Observer;
class Controller;
class BraitenbergVehicle;


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the MinGfx library to open up a window that
 *  includes a few buttons for controlling the simulation and can be used to
 *  draw circles and other computer graphics.
 *
 *  After constructing a new GraphicsArenaViewer, call Run to start and run the
 *  application. Run will not return until the application window is closed.
 *  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open UpdateSimulation will be called repeatedly,
 *  once per frame. Fill this in to update your simulation or perform any other
 *  processing that should happen over time as the simulation progresses.
 *
 *  Fill in the `On*()` methods as desired to respond to user input events.
 *
 *  Fill in the `Draw*()` methods to draw graphics on the screen using
 *  either the `nanovg` library or raw `OpenGL`.
 */
class GraphicsArenaViewer : public mingfx::GraphicsApp, public ArenaViewer {
 public:
  /**
   * @brief Constructor.
   *
   * @param width The width of Gui
   * @param height The height of Gui
   * @param controller The instance of Controller
   */
  explicit GraphicsArenaViewer(int width, int height,
                               Controller *controller);

  /**
   * @brief Destructor.
   *
   * `delete` the contained Arena.
   */
  ~GraphicsArenaViewer() override { delete arena_; }

  /** Used to setup the 2D GUI. */
  void InitNanoGUI() override;

  /**
   * @brief Informs the Arena of the new time, so that it can update.
   *
   * @param dt The new timestep.
   */
  void UpdateSimulation(double dt) override;

  /**
   * @brief Handle the user pressing the pause button on the GUI.
   *
   * This will freeze the graphics--no update, until the pause button is
   * pressed again.
   */
  void OnPlayingBtnPressed();

  /**
   * @brief Handle the user pressing the reset button on the GUI.
   *
   * This will completely remake the game. It does so by calling
   * the reset method located in controller, which will destroy
   * everything and make everything anew
   */
  void OnResetButtonPressed();


  /**
   * @brief A method to receive a new arena pointer from controller.
   *
   * When the reset button is pressed, a new arena must be received from the
   * controller.
   */
  void SetArena(Arena *arena) override;

  /**
   * @brief Called each time the mouse moves on the screen within the GUI
   * window.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   * @param[in] delta How far the mouse has moved.
   */
  void OnMouseMove(__unused const mingfx::Point2& pos,
                   __unused const mingfx::Vector2& delta) override {};

  /**
   * @brief Called each time the left mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseDown(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the left mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseUp(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseDown(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseUp(__unused const mingfx::Point2& pos) override {};

  /**
   * @brief Called each time a character key is pressed.
   *
   * @param[in] c Character representing a key that was pressed.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnKeyDown(__unused const char *c, __unused int modifiers) override {};

  /**
   * @brief Called each time a character key is released.
   *
   * @param[in] c Character representing a key that was released.
   * @param[in] modifiers Any modifier keys that were held with the key.
   */
  // virtual
  void OnKeyUp(
    __unused const char *c, __unused int modifiers) override { };

  /**
   * @brief Called each time a special (non-alphabetic) key is pressed.
   *
   * @param[in] key The key that was pressed.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyDown(__unused int key, __unused int scancode,
                        __unused int modifiers) override {}

  /**
   * @brief Called each time a special (non-alphabetic) key is released.
   *
   * @param[in] key The key that was released.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnSpecialKeyUp(__unused int key, __unused int scancode,
                      __unused int modifiers) override {};

  /**
   * @brief Draw the Arena with all of its entities using `nanogui`.
   *
   * This is the primary driver for drawing all entities in the Arena. It is
   * called at each iteration of `nanogui::mainloop()`.
   *
   * @param[in] ctx Context for nanogui.
   */
  void DrawUsingNanoVG(NVGcontext *ctx) override;

  /**
   * @brief Draw using `OpenGL`. This method is unimplemented, as currently
   * we are doing all drawing with `nanovg` in this application, so it is empty.
   */
  void DrawUsingOpenGL() override {}

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  GraphicsArenaViewer &operator=(const GraphicsArenaViewer &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  GraphicsArenaViewer(const GraphicsArenaViewer &other) = delete;

 private:
  void DrawArena(NVGcontext *ctx);

  /**
   * @brief Draw an Light in the Arena using `nanogui`.
   *
   * This function requires an active `nanovg` drawing context (`ctx`), so it
   * should probably only be called from with DrawUsingNanoVG.
   *
   * @param[in] ctx The `nanovg` context.
   * @param[in] light The Light handle.
   */
  void DrawEntity(NVGcontext *ctx, const class ArenaEntity *const entity);

  void AddEntityPanel(nanogui::Widget * panel);

  bool RunViewer() override;

  Controller *controller_;
  Arena *arena_;
  bool paused_{true};

  // buttons
  nanogui::Button *playing_button_{nullptr};
  nanogui::Button *reset_button_{nullptr};
  float xOffset_;
  bool nanogui_intialized_;
  nanogui::FormHelper* gui;
  nanogui::ref<nanogui::Window> window;

  Observer *GAV_obs_;
  DataBox text_l_container_;
  DataBox text_f_container_;
  DataBox text_bv_container_;
  BraitenbergVehicle *BV;

  WheelVelocity GAV_f_vel_;
  WheelVelocity GAV_l_vel_;
  WheelVelocity GAV_bv_vel_;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_GRAPHICS_ARENA_VIEWER_H_
