// Nour Ahmed, Muaaz Bdear
// Matrikal-Nr.:5200991, 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      help_scene.h
 * @author    Nour Ahmed, Muaaz Bdear
 * @email     nahmed@stud.hs-bremen.de, mbdear@stud.hs-bremen.de
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/

#include "help_scene.h"
#include "welcome_scene.h"

#include <memory>
#include <SDL.h>

using namespace myPong;

HelpGameScene::HelpGameScene(Game& game)
  : mGame(game),
    mTitleTextTexture(nullptr),
    mEndgameTexture(nullptr),
    mWinnerTexture(nullptr),
    mEndResultTexture(nullptr),
    mResultScoreTexture(nullptr),
    mInstructionsTexture(nullptr),
    mBackgroundImage(nullptr)
{
    mBackgroundImage = mGame.createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/final.png");
}

HelpGameScene::~HelpGameScene()
{

    SDL_DestroyTexture(mTitleTextTexture);
    SDL_DestroyTexture(mEndgameTexture);
    SDL_DestroyTexture(mEndResultTexture);
    SDL_DestroyTexture(mResultScoreTexture);
    SDL_DestroyTexture(mWinnerTexture);
    SDL_DestroyTexture(mInstructionsTexture);
}

void HelpGameScene::onDraw(SDL_Renderer& renderer)
{

}

void HelpGameScene::onUpdate()
{
  // ...
}

void HelpGameScene::onEnter()
{
  // ...
}

void HelpGameScene::onExit()
{
  // ...
}

void HelpGameScene::onKeyDown(SDL_KeyboardEvent& event)
{
  // ...
}

void HelpGameScene::onKeyUp(SDL_KeyboardEvent& event)
{
  // move player back to the welcome scene.
  switch (event.keysym.sym)
  {
  case SDLK_RETURN:
    mGame.setScene(std::make_shared<WelcomeScene>(mGame));
    break;
  }
}

void HelpGameScene::onTextInpt(std::string &text){
  // ...
}
void HelpGameScene::onMouseClick(int buttonID, int mouseX, int mouseY){

   /* std::string mouseCoord = "Left button was pressed!\n button pressed:"+
    std::to_string(buttonID) +
    "\n X: " + std::to_string(mouseX) +
    " Y: " + std::to_string(mouseY);
  mGame.ShowSimpleDialogBox("Mouse", mouseCoord.c_str());
  */

}
