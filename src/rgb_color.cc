/**
 * @file rgb_color.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
//! Namespaces for csci3081
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RgbColor::Set(RgbColorEnum value) {
  switch (value) {
    case kBlack:
      r = 0;
      g = 0;
      b = 0;
      break;
    case kWhite:
      r = 255;
      g = 255;
      b = 255;
      break;
    case kRed:
      r = 255;
      g = 0;
      b = 0;
      break;
    case kGreen:
      r = 0;
      g = 255;
      b = 0;
      break;
    case kBlue:
      r = 0;
      g = 0;
      b = 255;
      break;
    case kYellow:
      r = 255;
      g = 255;
      b = 50;
      break;
    case kOrange:
      r = 255;
      g = 130;
      b = 0;
      break;
    case kPurple:
      r = 75;
      g = 0;
      b = 150;
      break;
    case kMaroon:
      r = 122;
      g = 0;
      b = 25;
      break;
    case kGold:
      r = 255;
      g = 204;
      b = 51;
      break;
    case kGhost:
      r = 0;
      g = 0;
      b = 0;
      break;
    case kEnergyLevel3:
      r = 84;
      g = 11;
      b = 9;
      break;
    case kEnergyLevel2:
      r = 56;
      g = 7;
      b = 5;
      break;
    case kEnergyLevel1:
      r = 35;
      g = 4;
      b = 3;
      break;
    default:
      assert(false);
      break;
  }
}

//! Namespaces for csci3081
NAMESPACE_END(csci3081);
