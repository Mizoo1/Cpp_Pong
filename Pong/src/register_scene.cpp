// Nour Ahmed
// Matrikal-Nr.:5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      register_scene.cpp
 * @author    Nour Ahmed
 * @email     nahmed@stud.hs-bremen.de
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/

#include "register_scene.h"
#include "court_scene.h"
#include "game.h"
#include <sqlite3.h>
#include <SDL.h>

using namespace myPong;

RegisterScene::RegisterScene(Game &game) :
    mGame(game),
    mBackgroundImage(nullptr),
    focusIndex(0)
{
  mBackgroundImage = mGame.createImage("/home/Muaaz/Schreibtisch/tt/myPong-main/build/assets/reg.png");
}

RegisterScene::~RegisterScene()
{
  if (mBackgroundImage != nullptr) {
    SDL_DestroyTexture(mBackgroundImage);
  }
}

void RegisterScene::onDraw(SDL_Renderer &renderer)
{
  if (mBackgroundImage != nullptr) {
    // draw the background image
    SDL_RenderCopy(&renderer, mBackgroundImage, nullptr, nullptr);

    // draw foucs box indicator
    drawFocusBox(renderer, focusIndex);

    // render input text
    if (!mInputUserName.empty()) {
      SDL_Rect rect{ 505, 44, 145, 30 };
      SDL_Texture *texture = mGame.createText(mInputUserName.c_str());
      SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
      SDL_RenderCopy(&renderer, texture, nullptr, &rect);
    }

    // render input text
    if (!mInputPassword.empty()) {
      SDL_Rect rect{ 505, 84, 145, 30 };
      SDL_Texture *texture = mGame.createText(mInputPassword.c_str());
      SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
      SDL_RenderCopy(&renderer, texture, nullptr, &rect);
    }

    return;
  }
}

void RegisterScene::onUpdate()
{
  // ...
}

void RegisterScene::onEnter()
{
  // ...
}

void RegisterScene::onExit()
{
  // ...
}

void RegisterScene::onKeyDown(SDL_KeyboardEvent & /*event*/)
{
  // ...
}

void RegisterScene::onKeyUp(SDL_KeyboardEvent &event)
{
  // move player into the court scene to start the match.
  switch (event.keysym.sym) {
    case SDLK_RETURN: onButtonClickSelected(focusIndex); break;

    case SDLK_UP:
      --focusIndex;
      if (focusIndex < 0) { focusIndex = 5; }
      // play hit wall sound
      mGame.playSoundEffect(Game::HIT_PADDLE);
      break;

    case SDLK_DOWN:
      ++focusIndex;
      if (focusIndex > 5) { focusIndex = 0; }
      // play hit wall sound
      mGame.playSoundEffect(Game::HIT_PADDLE);
      break;

    case SDLK_F2:
      // start the game directly
      onButtonClickSelected(3);
      break;
  }
}

void RegisterScene::onTextInpt(std::string &text)
{
   std::cout << text;
  if (focusIndex == 0) { mInputUserName = text; }
  if (focusIndex == 1) { mInputPassword = text; }
}


void RegisterScene::onMouseClick(int buttonID, int mouseX, int mouseY)
{
 if ( (mouseX>500) && (mouseX<645) && (mouseY>45) && (mouseY<195)){
    focusIndex = mouseY/40 - 1; // it is zero-indexed
    onButtonClickSelected(focusIndex);
  }
}


void RegisterScene::onButtonClickSelected(int index)
{
  switch (index) {
    case 2: logIn(); break;
    case 3: mGame.setScene(std::make_shared<CourtScene>(mGame)); break;
  }
}

bool RegisterScene::logIn()
{
  mGame.addNewUser(mInputUserName, mInputPassword);
  bool re = mGame.checkUser(mInputUserName, mInputPassword);
  if (!re) {
    mGame.ShowDialogBox("Register New User Error", "Wrong username and/or password \nor click Cancel to play as Guest.\n\nTry again?");
    return re;
  }

  // login succeeded move to the court scene
  onButtonClickSelected(3);
  return re;
}

void RegisterScene::drawFocusBox(SDL_Renderer &renderer, int index)
{
  // draw focus rect
  SDL_SetRenderDrawColor(&renderer, 0xff, 0, 0, 0xff);

  SDL_Rect rect{ 500, (45 + index * 40), 145, 30 };
  SDL_RenderDrawRect(&renderer, &rect);

  // turn back the renderer draw color to white.
  SDL_SetRenderDrawColor(&renderer, 0xff, 0xff, 0xff, 0xff);
}
