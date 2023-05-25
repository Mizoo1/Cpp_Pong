// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      welcome_scene.h
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#ifndef MYPONG_WELCOME_SCENE_H
#define MYPONG_WELCOME_SCENE_H
#include "scene.h"
#include <string>
struct SDL_Texture;

namespace myPong {
class Game;

class WelcomeScene : public Scene {
public:
  WelcomeScene(Game &game);
  virtual ~WelcomeScene();

  void onDraw(SDL_Renderer &renderer) override;
  void onUpdate() override;
  void onEnter() override;
  void onExit() override;
  void onKeyDown(SDL_KeyboardEvent &event) override;
  void onKeyUp(SDL_KeyboardEvent &event) override;
  void onTextInpt(std::string &text) override;
  void onMouseClick(int buttonID, int mouseX, int mouseY) override;

  void onButtonClickSelected(int index);
  void drawFocusBox(SDL_Renderer &renderer, int index);
  bool logIn();

private:
  Game &mGame;
  SDL_Texture *mBackgroundImage;
  SDL_Texture *mTopicTexture;
  SDL_Texture *mLeftPlayerInstructions;
  SDL_Texture *mRightPlayerInstructions;
  SDL_Texture *mContinueInstructions;
  int focusIndex;
  std::string mInputUserName;
  std::string mInputPassword;
};
} // namespace myPong

#endif
