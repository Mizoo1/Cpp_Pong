// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      goal.cpp
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "goal.h"

using namespace myPong;

Goal::Goal(int x, int y, int width, int height) : mRect({ x, y, width, height })
{
  // calculate the half width and height.
  auto extentX = (width / 2);
  auto extentY = (height / 2);

  // define the dimensions for the CollisionDetector.
  mCollisionDetector.setCenterX(x + extentX);
  mCollisionDetector.setCenterY(y + extentY);
  mCollisionDetector.setExtentX(extentX);
  mCollisionDetector.setExtentY(extentY);
}
