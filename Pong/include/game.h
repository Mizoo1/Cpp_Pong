// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation
/**========================================================================
 * @file      game.h
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 * @brief     The main class of the game, It creates the window,
 *            renderer and manages the game loop and scenes.
 *            Game class creates the window, renderer and manages the game loop and scenes.
 *            It provides the access to the renderer and the resolution of the game window.
 *            It also provides a method to play sound effects and create textures from text or image files.
 *            It also keeps track of the player scores.
 *========================================================================**/
#ifndef MYPONG_GAME_H
#define MYPONG_GAME_H

#include "scene.h"
#include "userinfo.h"
#include "sqlitedatabase.h"

#include <array>
#include <string>


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;
struct Mix_Chunk;

namespace myPong
{
  // the game will end when score corsses this limit.
  // and the winner is the one that scores 1 goal more than this number
  const int MAX_GOALS_TO_WIN = 10;

  class Game
  {
  public:

    Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    void start();
    // function to set a new scene
    void setScene(ScenePtr scene);

    /*
    * Create SDL_Texture with a given text.
    * @param text: The text to be used for the texture
    */
    SDL_Texture* createText(const std::string& text);

    /*
    * Create SDL_Texture from a given image file.
    * @param fileName: The path of the png image file to be used for the texture
    */
    SDL_Texture* createImage(const char *fileName);
    enum SoundClips
    {
    HIT_PADDLE,
    HIT_WALL,
    GOAL,
    ERROR_
    };
    void playSoundEffect(SoundClips soundClip);
    int ShowDialogBox(const std::string& title, const std::string& message);
    int ShowSimpleDialogBox(const std::string &title, const std::string &message, const int &dialogType=1);

    bool checkUser(const std::string desiredUserName = "", const std::string desiredUserPassword = "");
    UserInfo& getCurrentUser(){return currentUser;}
    void addNewUser (const std::string& userName, const std::string& password){gameDB.insertNewUser(userName,password);}


    SDL_Renderer*  getRenderer(){return mRenderer;}
    //UserInfo&      getCurrentUser(){return currentUser;}


    /* Get the resolution (in a 2d-array) of the game canvas. */
    const std::array<int, 2>& getResolution() const { return mResolution; }

    /* Get the half-resolution (in a 2d-array) of the game canvas. */
    const std::array<int, 2>& getHalfResolution() const { return mHalfResolution; }

    /* Get a reference to the player scores via a 2d-array. */
    std::array<int, 2>& getPlayerScores() { return mPlayerScores; }
  private:
    SDL_Window*        mWindow;
    SDL_Renderer*      mRenderer;
    _TTF_Font*         mFont;
    Mix_Chunk*         wallHitSound;
    Mix_Chunk*         paddleHitSound;
    Mix_Chunk*         errorSound;
    Mix_Chunk*         goalSound;
    ScenePtr           mScene;
    std::array<int, 2> mResolution;
    std::array<int, 2> mHalfResolution;
    std::array<int, 2> mPlayerScores;

    SQLiteDatabase gameDB;
    UserInfo currentUser;
    std::string mTextInput;
  };
}

#endif
