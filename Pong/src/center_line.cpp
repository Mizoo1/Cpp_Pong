// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      cener_line.cpp
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "center_line.h"

using namespace myPong;

CenterLine::CenterLine(int x, int y, int width, int height) : mRect({ x, y, width, height })
{
    // This is the constructor of the CenterLine class, it takes in the x and y coordinates,
    // the width and height of the line as arguments
    // It is used to initialize the object and set its properties
    // The mRect variable is being initialized with the x, y, width, and height passed as arguments
}

void CenterLine::onDraw(SDL_Renderer& renderer)
{
  // draw the center line by forming a number squares as required.
  for (float y = static_cast<float>(mRect.y); y < mRect.h; y += (1.93f * mRect.w)) {
    SDL_Rect rect{ mRect.x, static_cast<int>(y), mRect.w, mRect.w };

    SDL_SetRenderDrawColor(&renderer, 0xcc, 0xff, 0x33, 0x50);
    SDL_RenderFillRect(&renderer, &rect);

    SDL_SetRenderDrawColor(&renderer, 0xff, 0xff, 0xff, 0xff);
  }
}
