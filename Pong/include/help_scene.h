// Muaaz Bdear,  Nour Ahmed
// Matrikal-Nr.: 5194038 , 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      help_scene.h
 * @author    Muaaz Bdear, Nour Ahmed
 * @email     nahmed@stud.hs-bremen.de, mbdear@stud.hs-bremen.de
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#ifndef HELP_SCENE_H
#define HELP_SCENE_H

#include "game.h"
#include "scene.h"


namespace myPong
{
  class HelpGameScene final : public Scene
  {
  public:
    HelpGameScene(Game& game);
    ~HelpGameScene();

    void onDraw(SDL_Renderer& renderer) override;
    void onUpdate() override;
    void onEnter() override;
    void onExit() override;
    void onKeyDown(SDL_KeyboardEvent& event) override;
    void onKeyUp(SDL_KeyboardEvent& event) override;
    void onTextInpt(std::string &text) override;
    void onMouseClick(int buttonID, int mouseX, int mouseY) override;


  private:
    Game&         mGame;
    SDL_Texture*  mBackgroundImage;
    SDL_Texture*  mTitleTextTexture;
    SDL_Texture*  mWinnerTexture;
    SDL_Texture*  mEndResultTexture;
    SDL_Texture*  mResultScoreTexture;
    SDL_Texture*  mEndgameTexture;
    SDL_Texture*  mInstructionsTexture;
  };
}
#endif // HELP_SCENE_H
