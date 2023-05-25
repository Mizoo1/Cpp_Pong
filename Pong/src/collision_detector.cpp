// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      collision.cpp
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "collision_detector.h"

#include <cmath>

using namespace myPong;

CollisionDetector::CollisionDetector() : mCenter({ 0, 0 }), mExtent({ 0, 0 })
{
}

bool CollisionDetector::collides(const CollisionDetector& other) const
{
  auto x = std::abs(mCenter[0] - other.mCenter[0]) < (mExtent[0] + other.mExtent[0]);
  auto y = std::abs(mCenter[1] - other.mCenter[1]) < (mExtent[1] + other.mExtent[1]);
  return x && y;
}
