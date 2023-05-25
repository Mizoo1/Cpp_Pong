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
#include "ball.h"
#include "court_scene.h"
#include <iostream>
#include "game.h"

using namespace myPong;

const float Ball::INITIAL_VELOCITY = 5.f;
const float Ball::VELOCITY_INCREASE = 1.f;
const float Ball::MAX_VELOCITY = 20.f;
auto movement = std::array<int, 2>();

Ball::Ball(CourtScene &scene, int x, int y, int width, int height)
    : mScene(scene),
      mBallImage(nullptr),
      mRect({x, y, width, height}),
      mVelocity(INITIAL_VELOCITY),
      mDirection({-0.5f, 0.5f})
{

    auto halfWidth = (width / 2);
    auto halfHeight = (height / 2);


    mCollisionDetector.setCenterX(x + halfWidth);
    mCollisionDetector.setCenterY(y + halfHeight);
    mCollisionDetector.setExtentX(halfWidth);
    mCollisionDetector.setExtentY(halfHeight);

    mBallImage = mScene.getGame().createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/yellowball.png");
}

void Ball::onDraw(SDL_Renderer &renderer)
{
  if (mBallImage != nullptr)
  {
    // draw the background image
    SDL_RenderCopy(&renderer, mBallImage, nullptr, &mRect);
    return;
  }
  // else draw a rect.
  SDL_RenderFillRect(&renderer, &mRect);
}

void Ball::onUpdate()
{
    bottomWallCollisionDetector = mScene.getBottomWall().getCollisionDetector();
    topWallCollisionDetector = mScene.getTopWall().getCollisionDetector();
    leftPaddleCollisionDetector = mScene.getLeftPaddle().getCollisionDetector();
    rightPaddleCollisionDetector = mScene.getRightPaddle().getCollisionDetector();
    leftGoalCollisionDetector = mScene.getLeftGoal().getCollisionDetector();
    rightGoalCollisionDetector = mScene.getRightGoal().getCollisionDetector();

    calculateMovement();

    applyMovement();

    checkCollision();
  }
void Ball::calculateMovement()
{

    movement[0] = static_cast<int>(mDirection[0] * mVelocity);
    movement[1] = static_cast<int>(mDirection[1] * mVelocity);
}

void Ball::applyMovement()
{
    mRect.x += movement[0];
    mRect.y += movement[1];
    mCollisionDetector.setCenterX(mCollisionDetector.getCenterX() + movement[0]);
    mCollisionDetector.setCenterY(mCollisionDetector.getCenterY() + movement[1]);
}
void Ball::checkCollision()
{

    if (mCollisionDetector.collides(bottomWallCollisionDetector))
    {
        handleBottomWallCollision();
    }
    else if (mCollisionDetector.collides(topWallCollisionDetector))
    {
        handleTopWallCollision();
    }
    else if (mCollisionDetector.collides(leftPaddleCollisionDetector))
    {
        handleLeftPaddleCollision();
    }
    else if (mCollisionDetector.collides(rightPaddleCollisionDetector))
    {
        handleRightPaddleCollision();
    }
    else if (mCollisionDetector.collides(rightGoalCollisionDetector))
    {
        handleRightGoalCollision();
    }
    else if (mCollisionDetector.collides(leftGoalCollisionDetector))
    {
        handleLeftGoalCollision();
    }
}

void Ball::handleBottomWallCollision()
{

    mRect.y = bottomWallCollisionDetector.getCenterY();
    mRect.y -= bottomWallCollisionDetector.getExtentY();
    mRect.y -= mRect.h;


    mCollisionDetector.setCenterX(mRect.x + mCollisionDetector.getExtentX());
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    mDirection[1] = -mDirection[1];


    mScene.getGame().playSoundEffect(Game::HIT_WALL);  // playSoundEffect(HIT_WALL);
}
void Ball::handleTopWallCollision()
{

    mRect.y = topWallCollisionDetector.getCenterY();
    mRect.y += topWallCollisionDetector.getExtentY();

    mCollisionDetector.setCenterX(mRect.x + mCollisionDetector.getExtentX());
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    mDirection[1] = -mDirection[1];


    mScene.getGame().playSoundEffect(Game::HIT_WALL);
}
void Ball::handleLeftPaddleCollision()
{
    std::cout << "Collision with left paddle detected!" << std::endl;

    mRect.x = leftPaddleCollisionDetector.getCenterX();
    mRect.x += leftPaddleCollisionDetector.getExtentX();

    mCollisionDetector.setCenterX(mRect.x + mCollisionDetector.getExtentX());
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    mDirection[0] = -mDirection[0];


    mVelocity += VELOCITY_INCREASE;
    mVelocity = std::min(mVelocity, MAX_VELOCITY);

    mScene.getGame().playSoundEffect(Game::HIT_PADDLE);
}
void Ball::handleRightPaddleCollision()
{
    std::cout << "Collision with right paddle detected!" << std::endl;
    // prevent the ball from moving through the paddle.
    mRect.x = rightPaddleCollisionDetector.getCenterX();
    mRect.x -= rightPaddleCollisionDetector.getExtentX();
    mRect.x -= mRect.w;

    // ensure that the CollisionDetector position gets updated as well.
    mCollisionDetector.setCenterX(mRect.x + mCollisionDetector.getExtentX());
    mCollisionDetector.setCenterY(mRect.y + mCollisionDetector.getExtentY());

    // invert the y-axis direction.
    mDirection[0] = -mDirection[0];

    // increase the velocity if possible.
    mVelocity += VELOCITY_INCREASE;
    mVelocity = std::min(mVelocity, MAX_VELOCITY);

    //play ball hit paddel sound
    mScene.getGame().playSoundEffect(Game::HIT_PADDLE);
}
void Ball::handleRightGoalCollision()
{
    mScene.addPlayerScore(0);
    //play goal sound
    mScene.getGame().playSoundEffect(Game::GOAL);

    // wait before processing the next frame
    SDL_Delay(50);
}
void Ball::handleLeftGoalCollision()
{
    mScene.addPlayerScore(1);

    mScene.getGame().playSoundEffect(Game::GOAL);

    SDL_Delay(50);
}

