/**
 * @file data_box.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_DATA_BOX_H_
#define SRC_DATA_BOX_H_

#include <MinGfx-1.0/mingfx.h>
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/** 
* @brief DataBox is a struct that contain two TextBox left and right.
*/
struct DataBox {
 public:
  //! left of TextBox
  nanogui::TextBox * left;
  //! right of TextBox
  nanogui::TextBox * right;
};

//! Namespaces for csci3081
NAMESPACE_END(csci2081);
#endif  // SRC_DATA_BOX_H_
