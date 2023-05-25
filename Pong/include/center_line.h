// Nour Ahmed
// Matrikal-Nr.: 5200991
// Assignment – Game Implementation
/**========================================================================
 * @file      center_line.h
 * @email     nahmed@stud.hs-bremen.de, nour
 * @author    Nour Ahmed
 * @createdOn 16.01.2023
 * @version   1.0.0
 * @brief     That header is responsible for drawing a center line on the screen.
 *            The class uses the SDL library for rendering and takes in the x and y coordinates,
 *            the height and width of the line as arguments in the constructor.
 *            The onDraw method is used to render the line on the screen using
 *            the SDL_Renderer object passed as a parameter. The mRect variable
 *            is used to store the properties of the line, such as its position and size.
 *========================================================================**/
#ifndef CENTER_LINE_H
#define CENTER_LINE_H
#include <SDL.h>

namespace myPong
{
  class CenterLine
  {
  public:
    CenterLine(int x, int y, int height, int widt);
    // This is the constructor of the CenterLine class, it takes in the x and y coordinates,
    // the height and width of the line as arguments
    // It is used to initialize the object and set its properties

    void onDraw(SDL_Renderer& renderer);
  private:
    SDL_Rect mRect;
  };
}

#endif // CENTER_LINE_H
