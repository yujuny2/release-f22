#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png): png_(png) {
  /** @todo [Part 2] */
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traversal_ = &traversal;
  colorPicker_ = &colorPicker;
  // ImageTraversal::Iterator it = traversal.begin();
  // while (!traversal.empty()) {
  //   unsigned x = (*it).x;
  //   unsigned y = (*it).y;
  //   png_.getPixel(x, y) = colorPicker.getColor((*it).x, (*it).y);
  //   ++it;
  // }

}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG png = png_;
  ImageTraversal::Iterator it = traversal_->begin();
  animation.addFrame(png);
  unsigned count = 0;
  
  while (it != traversal_->end()) {
    HSLAPixel color = colorPicker_->getColor((*it).x, (*it).y);
    HSLAPixel& pixel = png.getPixel((*it).x, (*it).y);
    pixel.h = color.h;
    pixel.s = color.s;
    pixel.l = color.l;
    pixel.a = color.a;
    ++it;
    count++;

    if ((count % frameInterval) == 0 || traversal_->empty()) {
      animation.addFrame(png);
    }
  }
  return animation;
}
