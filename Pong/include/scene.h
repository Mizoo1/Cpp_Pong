// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation
/**========================================================================
 * @file      scene.h
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 * @brief     This file contains the Scene class, which is the base class for all the scenes in the game.
 *            It defines the basic interface that all scenes must implement.
 *            The Scene class defines several virtual methods that must be overridden by derived classes.
 *            These methods include onDraw, onUpdate, onEnter, onExit, onKeyDown, onKeyUp, onTextInpt,
 *            onMouseMove, onMouseButtonDown and onMouseButtonUp.
 *            The Scene class also defines a typedef for shared pointer of Scene class.
 *========================================================================**/
#ifndef MYPONG_SCENE_H
#define MYPONG_SCENE_H

#include <memory>

struct SDL_KeyboardEvent;
struct SDL_Renderer;

namespace myPong
{
        /**
         * @brief The Scene class
         */
        class Scene
        {
        public:
                virtual void onDraw(SDL_Renderer& renderer) = 0;
                virtual void onUpdate() = 0;
                virtual void onEnter() = 0;
                virtual void onExit() = 0;
                virtual void onKeyDown(SDL_KeyboardEvent& event) = 0;
                virtual void onKeyUp(SDL_KeyboardEvent& event) = 0;
                virtual void onTextInpt(std::string &text) = 0;
            /**
             * @brief handle mouse click events
             *
             * @param buttonID which button is clicked (left, right, ...)
             * @param mouseX   x-coordinate of the mouse when clicked
             * @param mouseY   y-coordinate of the mouse when clicked
             */
            virtual void onMouseClick(int buttonID, int mouseX, int mouseY) = 0;
        };
        /**
         * @brief ScenePtr
         */
        typedef std::shared_ptr<Scene> ScenePtr;
}
#endif

