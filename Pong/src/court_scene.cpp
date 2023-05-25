// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      court_scene.cpp
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/

#include "court_scene.h"
#include "endgame_scene.h"
#include "wall.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <stdlib.h>
#include "score_indicator.h"

using namespace myPong;

// The amount of pause ticks to wait at start or after a goal.
#define PAUSE_TICKS 30

CourtScene::CourtScene(Game& game)
  : mGame(game),
    mBackgroundImage(nullptr),
    mTopWall(0, 50, game.getResolution()[0], BOX_WIDTH/10),
    mBottomWall(0, (game.getResolution()[1]- 40 - BOX_WIDTH), game.getResolution()[0], BOX_WIDTH/10),
    mCenterLine((game.getResolution()[0] /2) , BOX_WIDTH/6, BOX_WIDTH/6, game.getResolution()[1]),
    mLeftPaddle(*this, EDGE_OFFSET, (game.getResolution()[1] /2) - (PADDLE_HEIGHT/2), BOX_WIDTH/2, PADDLE_HEIGHT, true),
    mRightPaddle(*this, game.getResolution()[0] - EDGE_OFFSET - BOX_WIDTH/2, (game.getResolution()[1] /2) - (PADDLE_HEIGHT/2), BOX_WIDTH/2, PADDLE_HEIGHT),
    mBall(*this, game.getResolution()[0] /2 - (BOX_WIDTH/2), game.getResolution()[1] /2 - (BOX_WIDTH/2), BOX_WIDTH, BOX_WIDTH),
    mLeftGoal(-1000, 0, 1000 - BOX_WIDTH, game.getResolution()[1]),
    mRightGoal(game.getResolution()[0] + BOX_WIDTH, 0, 1000, game.getResolution()[1]),
    mLeftScoreIndicator(game, game.getHalfResolution()[0] - (70 + (game.getResolution()[0] / 10)),
                            10,
                            game.getResolution()[0] / 15,
                            game.getResolution()[1] / 20),
    mRightScoreIndicator(game, game.getHalfResolution()[0] + 70,
                             10,
                             game.getResolution()[0] / 15,
                             game.getResolution()[1] / 20),
                             mRemainingPauseTicks(PAUSE_TICKS)


{
      mBackgroundImage = mGame.createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/boardBackground.png");
}

CourtScene::~CourtScene()
{
    SDL_DestroyTexture(mBackgroundImage);
}

void CourtScene::onDraw(SDL_Renderer& renderer)
{
  // draw the background image
  SDL_RenderCopy(&renderer, mBackgroundImage, nullptr, nullptr);

  // disply current user info
  SDL_Rect rect{700, 10, 100, 30};

  // draw the lifes indicator
  rect.x=700; rect.y=555; rect.w=100; rect.h=30;
  SDL_RenderCopy(&renderer, mGame.createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/lifes.png"), nullptr, &rect);

  mTopWall.onDraw(renderer);
  mBottomWall.onDraw(renderer);

  // draw the center line if there is no background image
  if(mBackgroundImage == nullptr){mCenterLine.onDraw(renderer);}

  mLeftPaddle.onDraw(renderer);
  mRightPaddle.onDraw(renderer);
  mBall.onDraw(renderer);
  mLeftScoreIndicator.onDraw(renderer);
  mRightScoreIndicator.onDraw(renderer);

}

void CourtScene::onUpdate()
{
  if (mRemainingPauseTicks <= 0)
  {
    mLeftPaddle.onUpdate();
    mRightPaddle.onUpdate();
    mBall.onUpdate();
  }else {
      mRemainingPauseTicks--;
}
}

void CourtScene::onEnter()
{
  // seed the random with the time.
  srand(static_cast<unsigned int>(time(nullptr)));

  // clear the player scores.
  mGame.getPlayerScores()[0] = 0;
  mGame.getPlayerScores()[1] = 0;
}

void CourtScene::onExit()
{
  // TODO ...
}

void CourtScene::onKeyDown(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_w:
    mLeftPaddle.setMovement(Paddle::Movement::UP);
    break;
  case SDLK_s:
    mLeftPaddle.setMovement(Paddle::Movement::DOWN);
    break;
  case SDLK_UP:
    mRightPaddle.setMovement(Paddle::Movement::UP);
    break;
  case SDLK_DOWN:
    mRightPaddle.setMovement(Paddle::Movement::DOWN);
    break;
  }
}

void CourtScene::onKeyUp(SDL_KeyboardEvent& event)
{
  switch (event.keysym.sym) {
  case SDLK_w:
    if (mLeftPaddle.isMoving(Paddle::Movement::UP)) {
      mLeftPaddle.setMovement(Paddle::Movement::NONE);
    }
    break;
  case SDLK_s:
    if (mLeftPaddle.isMoving(Paddle::Movement::DOWN)) {
      mLeftPaddle.setMovement(Paddle::Movement::NONE);
    }
    break;
  case SDLK_UP:
    if (mRightPaddle.isMoving(Paddle::Movement::UP)) {
      mRightPaddle.setMovement(Paddle::Movement::NONE);
    }
    break;
  case SDLK_DOWN:
    if (mRightPaddle.isMoving(Paddle::Movement::DOWN)) {
      mRightPaddle.setMovement(Paddle::Movement::NONE);
    }
    break;
  }
}

void CourtScene::onTextInpt(std::string& /*text*/){
  //...
}

void CourtScene::onMouseClick(int buttonID, int mouseX, int mouseY)
{

 /* std::string mouseCoord = "Left button was pressed!\n button pressed:" + std::to_string(buttonID) +
                            "\n X: " + std::to_string(mouseX) +
                            " Y: " + std::to_string(mouseY);
  mGame.ShowSimpleDialogBox("Mouse", mouseCoord.c_str());
  */

}

void CourtScene::addPlayerScore(int playerIndex)
{
  resetEntities();
  auto& scores = mGame.getPlayerScores();
  scores[playerIndex]++;
  if (playerIndex == 0)
  {
    mLeftScoreIndicator.setValue(scores[playerIndex]);
  } else
  {
    mRightScoreIndicator.setValue(scores[playerIndex]);
  }
  mRemainingPauseTicks = PAUSE_TICKS;
  if (scores[playerIndex] > myPong::MAX_GOALS_TO_WIN)
  {
    mGame.setScene(std::make_shared<EndgameScene>(mGame));
  }
}

void CourtScene::resetEntities()
{
  // get a reference to screen half-resolution values.
  const auto& halfResolution = mGame.getHalfResolution();

  // place the ball back into the middle of the screen.
  const auto& ballCollisionDetector = mBall.getCollisionDetector();
  mBall.setX(halfResolution[0] - ballCollisionDetector.getExtentX());
  mBall.setY(halfResolution[1] - ballCollisionDetector.getExtentY());

  // randomize the ball direction.

  int random = rand() % 4;
  switch (random)
  {
    case 0: mBall.setDirection({  0.5f,  0.5f }); break;
    case 1: mBall.setDirection({  0.5f, -0.5f }); break;
    case 2: mBall.setDirection({ -0.5f,  0.5f }); break;
    case 3: mBall.setDirection({ -0.5f, -0.5f }); break;
  }
  // reset the ball velocity back to initial velocity.
  mBall.setVelocity(Ball::INITIAL_VELOCITY);

  // place the paddles back into the initial positions.
  const auto& paddleCollisionDetector = mLeftPaddle.getCollisionDetector();
  mLeftPaddle.setY(halfResolution[1] - paddleCollisionDetector.getExtentY());
  mRightPaddle.setY(halfResolution[1] - paddleCollisionDetector.getExtentY());

}







