// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      score_indicator.cpp
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "score_indicator.h"

using namespace myPong;

ScoreIndicator::ScoreIndicator(Game& thisGame, int x, int y, int width, int height) :
    mGame(thisGame),
    mRect({ x, y, width, height }),
    mValue(0)
{
  //...
}

void ScoreIndicator::onDraw(SDL_Renderer& renderer)
{
  //SDL_Rect rect{450, 10, 100, 30};
  // draw scoreBatch image
  SDL_RenderCopy(&renderer, mGame.createImage("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/scoreBatch.png"), nullptr, &mRect);
  SDL_RenderCopy(&renderer, mGame.createText(std::to_string(mValue).c_str()), nullptr, &mRect);
}
