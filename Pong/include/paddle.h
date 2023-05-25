// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation
/**========================================================================
 * @file      paddle.h
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 * @brief     The "Paddle" class is a part of the "myPong" namespace in the game
 *            implementation. It is responsible for creating and handling
 *            the paddle object that is used in the game. The class contains
 *            a constructor which takes in the scene, x and y coordinates, width,
 *            and height of the paddle as arguments. It also has functions to handle
 *            the movement of the paddle, drawing the paddle on the screen,
 *            and updating its position. Additionally, it has a private member variable
 *            "mCollisionDetector" which is used for collision detection with the ball
 *            and the paddle. The class also has a member variable to determine
 *            if it is the left or right paddle and uses this information for movement.
 *========================================================================**/
#ifndef PADDLE_H
#define PADDLE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "collision_detector.h"

namespace myPong
{
  class CourtScene;

  class Paddle
  {
      public:

        static const int VELOCITY;

        enum class Movement : int {
          UP    = -1,
          NONE  =  0,
          DOWN  =  1
        };
        /**
         * @brief Paddle Constructor for the Paddle class.
         * @param scene A reference to the CourtScene class, which controls the game logic.
         * @param x The x-coordinate of the paddle on the screen.
         * @param y The y-coordinate of the paddle on the screen.
         * @param width The width of the paddle.
         * @param height The height of the paddle.
         * @param isLeftPaddel A boolean indicating whether the paddle is the left paddle
         *  or the right paddle. Default is false (right paddle).
         */
        Paddle(CourtScene& scene, int x, int y, int width, int height, bool isLeftPaddel=false);
        /**
        * @brief onDraw - Function to draw the paddle on the game screen.
        * @param renderer - SDL renderer used to draw the paddle.
        */
        void onDraw(SDL_Renderer& renderer);
        void onUpdate();
        void updatePaddlePosition();
        void handleCollisionWithWalls();
        void handleCollisionWithTopWall();
        void handleCollisionWithBottomWall();

        /**
         * @brief setMovement
         * @param movement
         */
        void setMovement(Movement movement) { mMovement = movement; }
        /**
         * @brief isMoving
         * @param movement
         * @return true if the paddle's current movement is equal to
         *  the movement passed in as a parameter, otherwise false.
         */
        bool isMoving(Movement movement) const { return mMovement == movement;  }

        void setX(int x) { mRect.x = x; mCollisionDetector.setCenterX(x + mCollisionDetector.getExtentX()); }
        void setY(int y) { mRect.y = y; mCollisionDetector.setCenterY(y + mCollisionDetector.getExtentY()); }

        // get the collision detector of the paddle
        const CollisionDetector& getCollisionDetector() const { return mCollisionDetector; }
              CollisionDetector& getCollisionDetector()       { return mCollisionDetector; }
      private:
        CourtScene&       mScene;
        SDL_Rect          mRect;
        Movement          mMovement;
        CollisionDetector mCollisionDetector;
        bool              isLeft;
  };
}
#endif // PADDLE_H
