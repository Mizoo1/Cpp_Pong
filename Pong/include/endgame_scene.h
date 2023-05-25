// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      endgame_scene.h
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#ifndef MYPONG_ENDGAME_SCENE_H
#define MYPONG_ENDGAME_SCENE_H
#include "game.h"
#include "scene.h"


namespace myPong
{
  class EndgameScene final : public Scene
  {
  public:
    EndgameScene(Game& game);
    ~EndgameScene();

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
#endif // MYPONG_ENDGAME_SCENE_H
