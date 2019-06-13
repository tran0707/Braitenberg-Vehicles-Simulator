/**
 * @file controller.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_VIEWER_H_
#define SRC_ARENA_VIEWER_H_

#include "src/arena.h"

//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/**
 * @brief ArenaViewer draws the arena.
 */
class ArenaViewer {
 public:
  virtual ~ArenaViewer() {}

  /**
  * @brief RunViewer Function
  */
  virtual bool RunViewer() = 0;

  /**
  * @brief SetArena Function
  *
  * @param arena The new arena that want to set
  */
  virtual void SetArena(Arena* arena) = 0;
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_VIEWER_H_
