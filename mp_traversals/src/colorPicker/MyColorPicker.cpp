#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double hue, double increment): hue_(hue), increment_(increment) {}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  luminance_ = (luminance_ + increment_) > 1.0 ? 0 : luminance_ + increment_;
  HSLAPixel pixel(hue_, 0.5, luminance_);
  return pixel;
}
