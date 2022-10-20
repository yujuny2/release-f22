/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]) {
      return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int currentBest_dist = 0;
    int potential_dist = 0;
    for (int dim = 0; dim < Dim; dim++) {
      currentBest_dist += pow(target[dim] - currentBest[dim], 2);
      potential_dist += pow(target[dim] - potential[dim], 2);
    }
    if (currentBest_dist == potential_dist) {
      return currentBest > potential;
    }
    return currentBest_dist > potential_dist;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points_ = newPoints;
    buildTree(points_, 0, 0, newPoints.size() - 1, root);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  points_ = other.points_;
  buildTree(points_, 0, 0, points_.size() - 1, root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  // clear tree so that root is null before building new tree
  clear(root);
  size = rhs.size;
  points_ = rhs.points_;
  buildTree(points_, 0, 0, points_.size() - 1, root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
   root = NULL;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, 0, root);
}

// helper functions

// Partition
template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& points, int dim, unsigned left, unsigned right, unsigned pivotIndex) {
  // get pivot value
  Point<Dim> pivotValue = points[pivotIndex];

  // move pivot to the end by swapping
  Point<Dim> tmp = points[right];
  points[right] = points[pivotIndex];
  points[pivotIndex] = tmp;

  unsigned storeIndex = left;

  for (unsigned i = left; i < right; i++) {
    if (smallerDimVal(points[i], pivotValue, dim)) { // to-do: choose which dimension? and what is pivotValue? use smallerDimVal?
      // swap points[storeIndex] and points[i]
      tmp = points[storeIndex];
      points[storeIndex] = points[i];
      points[i] = tmp;
      
      // increment storeIndex
      storeIndex++;
    }
  }

  // swap points[right] and points[storeIndex]
  tmp = points[right];
  points[right] = points[storeIndex];
  points[storeIndex] = tmp;

  return storeIndex;
}

// Quick select
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& points, int dim, unsigned left, unsigned right, unsigned k) {
  while (true) {
    if (left == right) {
      return points[left];
    }

    // select pivotIndex between left and right
    unsigned pivotIndex = k;
    pivotIndex = partition(points, dim, left, right, pivotIndex);

    if (k == pivotIndex) {
      return points[k];
    }
    if (k < pivotIndex) {
      right = pivotIndex - 1;
    } else {
      left = pivotIndex + 1;
    }
  }
}

// Build Tree
template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, unsigned left, unsigned right, KDTree<Dim>::KDTreeNode*& subroot) {
  // continue if we have points left to include
  if (left <= right && !points.empty() && left >= 0 && left < points.size() && right >= 0 && right < points.size()) {
    unsigned middle = (left + right) / 2;
    Point<Dim> midpoint = select(points, dim, left, right, middle);
    subroot = new KDTreeNode(midpoint);
    size++;
    buildTree(points, (dim + 1) % Dim, left, middle - 1, subroot->left);
    buildTree(points, (dim + 1) % Dim, middle + 1, right, subroot->right);
  }
}

// Clear for destructor
template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode*& subroot) {
  if (subroot) {
    clear(subroot->left);
    clear(subroot->right);
    delete subroot;
  }
}

// find nearest neighbor
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int dim, KDTree<Dim>::KDTreeNode* subroot) const {
  // return the point of current node if it is a leaf
  if (!subroot->left && !subroot->right) return subroot->point;

  Point<Dim> nearest = subroot->point;
  bool recursedLeft = false;

  // if query[dim] is smaller than subroot->point[dim]
  if (smallerDimVal(query, subroot->point, dim)) {
    // recurse left
    if (subroot->left) {
      nearest = findNearestNeighbor(query, (dim + 1) % Dim, subroot->left);
    } 
    recursedLeft = true;
  } else {
    // recurse right
    if (subroot->right) {
      nearest = findNearestNeighbor(query, (dim + 1) % Dim, subroot->right);
    } 
  }

  // if the point of subroot is closer to the query than current nearest
  if (shouldReplace(query, nearest, subroot->point)) {
    nearest = subroot->point;
  }

  // radius between query and nearest
  double radius = 0;
  for (int i = 0; i < Dim; i++) {
    radius += pow(query[i] - nearest[i], 2);
  }

  // split distance
  double splitDistance = pow(subroot->point[dim] - query[dim], 2);

  Point<Dim> tempNearest = nearest;
  if (splitDistance <= radius) {
    if (recursedLeft) {
      if (subroot->right) {
        tempNearest = findNearestNeighbor(query, (dim + 1) % Dim, subroot->right);
      }
    } else {
      if (subroot->left) {
        tempNearest = findNearestNeighbor(query, (dim + 1) % Dim, subroot->left);
      }
    }
    // if tempNearest is closer to the query than nearest
    if (shouldReplace(query, nearest, tempNearest)) {
      nearest = tempNearest;
    }
  }

  return nearest;
}
