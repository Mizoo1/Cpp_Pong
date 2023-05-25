#ifndef SCORE_INDICATOR_H
#define SCORE_INDICATOR_H
#include "game.h"

#include <SDL2/SDL.h>


namespace myPong
{
  class ScoreIndicator final
  {
  public:
    ScoreIndicator(Game& thisGame, int x, int y, int width, int height);

    void onDraw(SDL_Renderer& renderer);
    void setValue(int value) { mValue = value; }
  private:
    Game& mGame;
    int mValue;
    SDL_Rect mRect;
  };
}
#endif // SCORE_INDICATOR_H
