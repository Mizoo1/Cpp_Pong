// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation
/**=================================================================================================
 * @file      goal.h
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 * @brief     The Goal class is used to create a goal object that represents the two goals in the game.
 *            This class contains the properties of the goals such as their position and size, and also
 *            contains collision detection functionality to check for collisions between the ball and the goals.
 *            The class contains methods to set the position and size of the goals, and also methods to access
 *            the collision detector object used for collision detection.
 *================================================================================================**/

#ifndef GOAL_H
#define GOAL_H
#include <SDL.h>

#include "collision_detector.h"

namespace myPong
{
  class Goal final
  {
  public:
    /*
    * It takes in the x and y coordinates, width and height of the goal as arguments.
    * It is used to initialize the object and set its properties.
    */
    Goal(int x, int y, int width, int height);

    void setX(int x) { mRect.x = x; mCollisionDetector.setCenterX(x + mCollisionDetector.getExtentX()); }
    void setY(int y) { mRect.y = y; mCollisionDetector.setCenterY(y + mCollisionDetector.getExtentY()); }
    /*
    * The getCollisionDetector function is used to get the collision detector object of the goal.
    */
    const CollisionDetector& getCollisionDetector() const { return mCollisionDetector; }
          CollisionDetector& getCollisionDetector()       { return mCollisionDetector; }
  private:
    SDL_Rect          mRect;
    CollisionDetector mCollisionDetector;
  };
}
#endif // GOAL_H
