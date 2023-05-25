// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      ball.h
 * @brief     The ball entity that contains definitions for the game ball.
 *
 * This class presents the ball entity used in the court scene. Ball is an
 * entity that goes around the scene by bouncing from the other entities.
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#ifndef BALL_H
#define BALL_H
#include "collision_detector.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <array>

namespace myPong
{
    class CourtScene;
    // This line forward declares the CourtScene class, which is used by the Ball class

    class Ball
    {
        public:

          static const float INITIAL_VELOCITY;

          static const float VELOCITY_INCREASE;

          static const float MAX_VELOCITY;

          CollisionDetector bottomWallCollisionDetector;
          CollisionDetector topWallCollisionDetector;
          CollisionDetector leftPaddleCollisionDetector;
          CollisionDetector rightPaddleCollisionDetector;
          CollisionDetector leftGoalCollisionDetector;
          CollisionDetector rightGoalCollisionDetector;
          Ball(CourtScene &scene, int x, int y, int width, int height);

          void onDraw(SDL_Renderer &renderer);
          // to render the ball on the screen
          // using the SDL_Renderer object passed as a parameter.
          void onUpdate();
          //====================================================
          void calculateMovement();
          void applyMovement();
          void checkCollision();
          void handleBottomWallCollision();
          void handleTopWallCollision();
          void handleLeftPaddleCollision();
          void handleRightPaddleCollision();
          void handleRightGoalCollision();
          void handleLeftGoalCollision();
          //=====================================================
          enum SoundClips
          {
          HIT_PADDLE,
          HIT_WALL,
          GOAL,
          ERROR_
          };
          // This function updates the ball's position and state on the screen.
          void setX(int x)
          {
            mRect.x = x;
            mCollisionDetector.setCenterX(x + mCollisionDetector.getExtentX());
            /* to set the x position of the ball,
             * it takes an integer as an argument and sets the x position
             * of the ball's rectangle and the collision detector.
             */
          }
          void setY(int y)
          {
            mRect.y = y;
            mCollisionDetector.setCenterY(y + mCollisionDetector.getExtentY());
          }


          void setDirection(const std::array<float, 2> &direction) {mDirection = direction;}
            // to set the direction of the ball,

          void setVelocity(float velocity) { mVelocity = velocity; }

          const CollisionDetector &getCollisionDetector() const {return mCollisionDetector;}
            //to get the collision detector of the ball, they return a reference to the mCollisionDetector object.

          CollisionDetector &getCollisionDetector() { return mCollisionDetector; }

        private:
          CourtScene &mScene;

          SDL_Texture *mBallImage;

          SDL_Rect mRect;

          CollisionDetector mCollisionDetector;

          float mVelocity;

          std::array<float, 2> mDirection;


    };
} // namespace myPong
#endif // BALL_H
