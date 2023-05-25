// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      court_scene.h
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 16.01.2023
 * @version   1.0.0
 * @brief     This class is a scene in the game, it contains all the entities
 *            that make up the court, such as the ball, paddles, walls, and goals.
 *            It also has several functions to handle different events and updates of the scene.
 *            Additionally, it has several getter functions to access the different entities within the scene.
 *=========================================================================**/
#ifndef MYPONG_COURT_SCENE_H
#define MYPONG_COURT_SCENE_H

#include "scene.h"
#include "game.h"
#include "ball.h"
#include "center_line.h"
#include "goal.h"
#include "paddle.h"
#include "wall.h"
#include "score_indicator.h"


#include <array>

namespace myPong
{
  class Game;
  class CourtScene : public Scene
  {
  public:

    static const int BOX_WIDTH = 20;

    static const int WALL_HEIGHT = BOX_WIDTH;

    static const int PADDLE_HEIGHT = 100;

    static const int EDGE_OFFSET = 10;

    CourtScene(Game& game);
    virtual ~CourtScene();

    void onDraw(SDL_Renderer& renderer) override;
    void onUpdate() override;
    void onEnter() override;

    //This function is called when the scene is entered
    void onExit() override;
    void onKeyDown(SDL_KeyboardEvent& event) override;
    void onKeyUp(SDL_KeyboardEvent& event) override;
    void onTextInpt(std::string &text) override;
    void onMouseClick(int buttonID, int mouseX, int mouseY) ;

    void addPlayerScore(int playerIndex);
    void resetEntities();
    //This function is used to reset the entities in the scene

    const Game& getGame() const { return mGame; }
          Game& getGame()       { return mGame; }

    const Wall& getTopWall() const  { return mTopWall; }
          Wall& getTopWall()        { return mTopWall; }

    const Wall& getBottomWall() const { return mBottomWall; }
          Wall& getBottomWall()       { return mBottomWall; }

    const CenterLine& getCenterLine() const { return mCenterLine; }
          CenterLine& getCenterLine()       { return mCenterLine; }

    const Paddle& getLeftPaddle() const { return mLeftPaddle; }
          Paddle& getLeftPaddle()       { return mLeftPaddle; }

    const Paddle& getRightPaddle() const { return mRightPaddle; }
          Paddle& getRightPaddle()       { return mRightPaddle; }

    const Goal& getLeftGoal() const { return mLeftGoal; }
          Goal& getLeftGoal()       { return mLeftGoal; }

    const Goal& getRightGoal() const  { return mRightGoal; }
          Goal& getRightGoal()        { return mRightGoal; }



  private:
    Game& mGame;
    SDL_Texture     *mBackgroundImage;
    Wall            mTopWall;
    Wall            mBottomWall;
    CenterLine      mCenterLine;
    Paddle          mLeftPaddle;
    Paddle          mRightPaddle;
    Ball            mBall;
    Goal            mLeftGoal;
    Goal            mRightGoal;
    ScoreIndicator  mLeftScoreIndicator;
    ScoreIndicator  mRightScoreIndicator;
    int             mRemainingPauseTicks;
  };
} // namespace myPong
#endif // MYPONG_COURT_SCENE_H
