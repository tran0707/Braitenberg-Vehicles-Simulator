/**
 * @file rgb_color.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RGB_COLOR_H_
#define SRC_RGB_COLOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

//! Enum for all Rgb Color in this simulation
enum RgbColorEnum {
  kRed,
  kGreen,
  kBlue,
  kYellow,
  kOrange,
  kPurple,
  kWhite,
  kBlack,
  kMaroon,
  kGold,
  kGhost,
  kEnergyLevel3,
  kEnergyLevel2,
  kEnergyLevel1
};

/*******************************************************************************
 * Struct Definitions
 ******************************************************************************/
/**
 * @brief Struct representing a rgb_color.
 *
 * Internally uses RGBA values to represent the rgb_color.
 */
struct RgbColor {
 public:
  //! r component of RgbColor
  int r{0};
  //! g component of RgbColor
  int g{0};
  //! b component of RgbColor
  int b{0};

  /**
   * @brief Default constructor.
   *
   * Initialize RGB all to 0 (kWhite).
   */
  RgbColor() {}

  /**
   * @brief Constructor for Rgb_Color.
   *
   * @param r_in The R component of the rgb_color.
   * @param g_in The G component of the rgb_color.
   * @param b_in The B component of the rgb_color.
   */
  RgbColor(int r_in, int g_in, int b_in) : r(r_in), g(g_in), b(b_in) {}

  /**
  * @brief Constructor for RgbColor
  *
  * @param value The value of RgbColorEnum
  */
  explicit RgbColor(RgbColorEnum value) : r(0), g(0), b(0) {
    Set(value);
  }

  /**
  * @brief Setter function to set RgbColor
  *
  * @param value The value of RgbColor want to set
  */
  void Set(RgbColorEnum value);

  //! Copy Constructor
  bool operator==(const RgbColor& color) const {
    return r == color.r && g == color.g && b == color.b;
  }
};

//! Namespaces for csci3081
NAMESPACE_END(csci3081);

#endif  // SRC_RGB_COLOR_H_
