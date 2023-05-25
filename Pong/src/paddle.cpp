// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      paddle.cpp
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "paddle.h"
#include "court_scene.h"

#include <iostream>

using namespace myPong;

const int Paddle::VELOCITY = 8;

Paddle::Paddle(CourtScene &scene, int x, int y, int width, int height, bool isLeftPaddel)
    : mScene(scene),
      mRect({x, y, width, height}),
      mMovement(Movement::NONE)
{
    // calculate half width and height.
    auto halfWidth = (width / 2);
    auto halfHeight = (height / 2);

    // construct an CollisionDetector for the object.
    mCollisionDetector.setCenterX(x + halfWidth);
    mCollisionDetector.setCenterY(y + halfHeight);
    mCollisionDetector.setExtentX(halfWidth);
    mCollisionDetector.setExtentY(halfHeight);

}
void Paddle::onDraw(SDL_Renderer &renderer)
{
  // change the renderer draw color to light blue for left and red for right.

  if (isLeft){
    SDL_SetRenderDrawColor(&renderer, 0x00, 0xff, 0xff, 0xff);
  }else{
    SDL_SetRenderDrawColor(&renderer, 0xff, 0, 0x0, 0xff);
  }

  SDL_RenderFillRect(&renderer, &mRect);

  // turn back the renderer draw color to white.
  SDL_SetRenderDrawColor(&renderer, 0xff, 0xff, 0xff, 0xff);
}

void Paddle::onUpdate()
{
  // update paddle position only if the paddle is moving.
  if (mMovement == Movement::NONE)
      return;

  updatePaddlePosition();
  handleCollisionWithWalls();
}

void Paddle::updatePaddlePosition()
{
  auto movement = (int)mMovement * VELOCITY;
  mRect.y += movement;
  mCollisionDetector.setCenterY(mCollisionDetector.getCenterY() + movement);
}

void Paddle::handleCollisionWithWalls()
{
  if (mMovement == Movement::UP)
  {
    handleCollisionWithTopWall();
  }
  else
  {
    handleCollisionWithBottomWall();
  }
}

void Paddle::handleCollisionWithTopWall()
{
  const auto &wallCollisionDetector = mScene.getTopWall().getCollisionDetector();
  if (mCollisionDetector.collides(wallCollisionDetector))
  {
    // prevent the paddle from moving through the wall.
    mRect.y = wallCollisionDetector.getCenterY();
    mRect.y += wallCollisionDetector.getExtentY();

    // ensure that the CollisionDetector position gets updated as well.
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    // stop the movement.
    mMovement = Movement::NONE;
  }
}

void Paddle::handleCollisionWithBottomWall()
{
  const auto &wallCollisionDetector = mScene.getBottomWall().getCollisionDetector();
  if (mCollisionDetector.collides(wallCollisionDetector))
  {
    // prevent the paddle from moving through the wall.
    mRect.y = wallCollisionDetector.getCenterY();
    mRect.y -= wallCollisionDetector.getExtentY();
    mRect.y -= mRect.h;

    // ensure that the CollisionDetector position gets updated as well.
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    // stop the movement.
    mMovement = Movement::NONE;
  }
}

