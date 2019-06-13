/**
 * @file controller.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <vector>

#include "src/arena.h"
#include "src/common.h"
#include "src/arena_viewer.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Controller that mediates Arena and GraphicsArenaViewer communication.
 *
 * The Controller instantiates the Arena and the GraphicsArenaViewer. The
 * viewer contains the main loop that keeps it live, but at each update, the
 * viewer sends a message to the controller to update its time.
 *
 * Other types of communication between Arena and Viewer include:
 * - keypresses intercepted by the Viewer.
 * - Play/Pause/New Game user input via the Viewer.
 * - Game status from arena to the viewer.
 **/
class Controller {
 public:
  /**
   * @brief Controller's constructor that will create Arena and Viewer.
   */
  Controller(int argc, char **argv);
  Controller(const Controller &obj) = delete;  // copy constructor

  virtual ~Controller();

  /**
   * @brief Function to create viewer.
   *
   * @param width The width of Gui
   * @param height The height of Gui
   */
  virtual ArenaViewer* CreateViewer(int width, int height);

  /**
   * @brief Run launches the graphics and starts the game.
   */
  void Run();

  /**
   * @brief AdvanceTime is communication from the Viewer to advance the
   * simulation.
   */
  void AdvanceTime(double dt);

 /**
  * @brief Completely destroy and remake the arena
  */
  void Reset();


  Controller &operator=(const Controller &other) = delete;

  /**
   * @brief Add quptes around string
   */
  std::string add_quotes(std::string word);

  /**
   * @brief To determine if quotes should be put around the parsed word
   */
  inline bool in_number_set(std::string word);

  /**
   * @brief boolean function that check csv file extension
   */
  bool cvs_file_extension(std::string filename);

  /**
   * @brief boolean function that check json file extension
   */
  bool json_file_extension(std::string filename);

  /**
   * @brief Convert/Adapt csv back to json
   */
  std::string adapt_csv(char **argv);

 private:
  double last_dt{0};
  Arena* arena_{nullptr};
  ArenaViewer* viewer_{nullptr};
  std::vector<ArenaViewer*> viewers_;
  json_value* config_;
  bool csv_ext;
  bool json_ext;
  double input_xdim;
  double input_ydim;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_CONTROLLER_H_
