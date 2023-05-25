// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation
/**========================================================================
 * @file      welcome_scene.cpp
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "welcome_scene.h"
#include "court_scene.h"
#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <register_scene.h>

using namespace myPong;

WelcomeScene::WelcomeScene(Game &game)
    : mGame(game), mBackgroundImage(nullptr), mTopicTexture(nullptr),
      mLeftPlayerInstructions(nullptr), mRightPlayerInstructions(nullptr),
      mContinueInstructions(nullptr), focusIndex(0)
{
    // Load the background image using the createImage function from the game object
  mBackgroundImage = mGame.createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/intro.png");
  if (mBackgroundImage == nullptr)
  {
      // If the background image was not successfully loaded, create the topic text
    mTopicTexture = mGame.createText("SDL2 PONG");
    // Create the left player instructions text
    mLeftPlayerInstructions =
        mGame.createText("Controls for the left player: W and S");
    // Create the right player instructions text
    mRightPlayerInstructions = mGame.createText(
        "Controls for the right player: UP-ARROW and DOWN-ARROW");
    // Create the continue instructions text
    mContinueInstructions =
        mGame.createText("Press [ENTER] to start the match");
  }
}

WelcomeScene::~WelcomeScene()
{
  if (mBackgroundImage != nullptr)
  {
    SDL_DestroyTexture(mBackgroundImage);
  } else {
    SDL_DestroyTexture(mTopicTexture);
    SDL_DestroyTexture(mLeftPlayerInstructions);
    SDL_DestroyTexture(mRightPlayerInstructions);
    SDL_DestroyTexture(mContinueInstructions);
  }
}

void WelcomeScene::onDraw(SDL_Renderer &renderer)
{
  if (mBackgroundImage != nullptr)
  {
    // draw the background image
    SDL_RenderCopy(&renderer, mBackgroundImage, nullptr, nullptr);

    // draw foucs box indicator
    drawFocusBox(renderer, focusIndex);

    // render input text
    if (!mInputUserName.empty())
    {
      SDL_Rect rect{505, 44, 145, 30};
      SDL_Texture *texture = mGame.createText(mInputUserName.c_str());
      SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
      SDL_RenderCopy(&renderer, texture, nullptr, &rect);
    }

    // render input text
    if (!mInputPassword.empty())
    {
      SDL_Rect rect{505, 84, 145, 30};
      SDL_Texture *texture = mGame.createText(mInputPassword.c_str());
      SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
      SDL_RenderCopy(&renderer, texture, nullptr, &rect);
    }

    return;
  }

  // else draw native blocks

  // draw the topic of the game.
  SDL_Rect rect{0, 100, 0, 0};
  SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

  // draw the left player control instructions.
  SDL_QueryTexture(mLeftPlayerInstructions, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 200;
  SDL_RenderCopy(&renderer, mLeftPlayerInstructions, nullptr, &rect);

  // draw the right player control instructions.
  SDL_QueryTexture(mRightPlayerInstructions, nullptr, nullptr, &rect.w,
                   &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 250;
  SDL_RenderCopy(&renderer, mRightPlayerInstructions, nullptr, &rect);

  // draw the instructions how to continue to court scene.
  SDL_QueryTexture(mContinueInstructions, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 400;
  SDL_RenderCopy(&renderer, mContinueInstructions, nullptr, &rect);
}

void WelcomeScene::onUpdate()
{
  // ...
}

void WelcomeScene::onEnter()
{
  // ...
}

void WelcomeScene::onExit()
{
  // ...
}

void WelcomeScene::onKeyDown(SDL_KeyboardEvent &event)
{
  // ...
}

void WelcomeScene::onKeyUp(SDL_KeyboardEvent &event)
{
  // move player into the court scene to start the match.
  switch (event.keysym.sym)
  {
  case SDLK_RETURN: onButtonClickSelected(focusIndex); break;

  case SDLK_UP:
    --focusIndex;
    if (focusIndex < 0) { focusIndex = 5; }
    // play hit wall sound
    mGame.playSoundEffect(Game::HIT_WALL);
    break;

  case SDLK_DOWN:
    ++focusIndex;
    if (focusIndex > 5) { focusIndex = 0; }
    // play hit wall sound
    mGame.playSoundEffect(Game::HIT_WALL);
    break;

  case SDLK_SPACE:
    // start the game directly
    onButtonClickSelected(3);
    break;
  }
}



void WelcomeScene::onTextInpt(std::string &text)
{
  // std::cout << text;
  if (focusIndex == 0)
  {
    mInputUserName = text;
  }
  if (focusIndex == 1)
  {
    mInputPassword = text;
  }
}

void WelcomeScene::onMouseClick(int buttonID, int mouseX, int mouseY)
{
  if ( (mouseX>500) && (mouseX<645) && (mouseY>45) && (mouseY<275)){
    focusIndex = mouseY/40 -1 ; // it is zero-indexed
/*
    std::string mouseCoord = "Left button was pressed!\n button pressed:" + std::to_string(buttonID) +
                              "\n X: " + std::to_string(mouseX) +
                              " Y: " + std::to_string(mouseY) +
                              " focusIndex: " + std::to_string(focusIndex);
    mGame.ShowSimpleDialogBox("Mouse", mouseCoord.c_str());

*/
    onButtonClickSelected(focusIndex);
  }
}
void WelcomeScene::onButtonClickSelected(int index)
{
  switch (index)
  {
  case 2: logIn(); break;
  case 3: mGame.setScene(std::make_shared<CourtScene>(mGame)); break;
  case 4: mGame.ShowSimpleDialogBox("myPong", "Settings will go here"); break;
  case 5: mGame.ShowSimpleDialogBox("myPong", "Help will go here"); break;

  }
}

bool WelcomeScene::logIn()
{
  bool re = mGame.checkUser(mInputUserName, mInputPassword);
  std::cout << "\nre: " << re << "\n";
  if (re) { // login succeeded move to the court scene
    onButtonClickSelected(3);
    return re;
  }

  // login failed. Show error and ask to register
  int reply = mGame.ShowDialogBox("Login Error", "Wrong username and/or password.\nClick No to try again\n\n Register as a new user?");
  if (reply == 1) { // login succeeded move to the court scene
    onButtonClickSelected(10);
    return reply;
  }

  return re;
}
void WelcomeScene::drawFocusBox(SDL_Renderer &renderer, int index)
{
  // draw focus rect
  SDL_SetRenderDrawColor(&renderer, 0xff, 0, 0, 0xff);

  SDL_Rect rect{500, (45 + index * 40), 145, 30};
  SDL_RenderDrawRect(&renderer, &rect);

  // turn back the renderer draw color to white.
  SDL_SetRenderDrawColor(&renderer, 0xff, 0xff, 0xff, 0xff);
}
