
// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation
/**========================================================================
 * @file      wall.h
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 * @brief     This class represents a wall in the game, it holds the collision
 *            detector and the rectangle for the wall
 *========================================================================**/
#ifndef WALL_H
#define WALL_H

#include "collision_detector.h"
#include <SDL.h>

namespace myPong
{
  class Wall
  {
  public:
      /**
     * @brief Wall
     * @param x the x-coordinate of the top-left corner of the wall
     * @param y the y-coordinate of the top-left corner of the wall
     * @param width the width of the wall
     * @param height the height of the wall
     */
    Wall(int x, int y, int width, int height);
    const CollisionDetector& getCollisionDetector() const { return mCollisionDetector; }
          CollisionDetector& getCollisionDetector()       { return mCollisionDetector; }
     /**
     * @brief onDraw
     * @param renderer
     */
    void onDraw(SDL_Renderer& renderer);

  private:
    SDL_Rect mRect;
        CollisionDetector     mCollisionDetector;
  };
}

#endif // WALL_H
