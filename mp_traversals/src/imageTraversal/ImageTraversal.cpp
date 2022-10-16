#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(): traversal(NULL) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal_type, PNG png, Point start, double tolerance) {
  traversal = traversal_type;
  png_ = png;
  startingPoint = start;
  tolerance_ = tolerance;
  current = traversal->peek();
  visited.resize(png.width());
  for (unsigned i = 0; i < visited.size(); i++) {
    visited[i].resize(png.height());
    for (unsigned j = 0; j < visited[0].size(); j++) {
      visited[i][j] = false;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal->empty()) {
    // visited.push_back(current);
    visited[current.x][current.y] = true;
    traversal->add(current);

    // check if 1. point is in range; 2. tolerance is within range; 3. the node is not visited
    Point right(current.x + 1, current.y);
    Point down(current.x, current.y + 1);
    Point left(current.x - 1, current.y);
    Point up(current.x, current.y - 1);

    if (right.x < png_.width() && right.x >= 0 && right.y < png_.height() && right.y >= 0) {
      double delta = calculateDelta(png_.getPixel(startingPoint.x, startingPoint.y), png_.getPixel(right.x, right.y));
      if (delta < tolerance_ && !visited[right.x][right.y]) {
        traversal->add(right);
      }
    }
    if (down.y < png_.height() && down.x >= 0 && down.x < png_.width() && down.y >= 0) {
      double delta = calculateDelta(png_.getPixel(startingPoint.x, startingPoint.y), png_.getPixel(down.x, down.y));
      if (delta < tolerance_ && !visited[down.x][down.y]) {
        traversal->add(down);
      }
    }
    if (left.x >= 0  && left.x < png_.width() && left.y < png_.height() && left.y >= 0) {
      double delta = calculateDelta(png_.getPixel(startingPoint.x, startingPoint.y), png_.getPixel(left.x, left.y));
      if (delta < tolerance_ && !visited[left.x][left.y]) {
        traversal->add(left);
      }
    }
    if (up.y >= 0  && up.x >= 0 && up.y < png_.height() && up.x < png_.width()) {
      double delta = calculateDelta(png_.getPixel(startingPoint.x, startingPoint.y), png_.getPixel(up.x, up.y));
      if (delta < tolerance_ && !visited[up.x][up.y]) {
        traversal->add(up);
      }
    }

    while (!traversal->empty() && visited[current.x][current.y]) {
      current = traversal->pop();
    }

    if (traversal->empty() && !visited[current.x][current.y]) {
      traversal->add(current);
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

