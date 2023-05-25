// Muaaz Bdear
// Matrikal-Nr.: 5194038
// Assignment – Game Implementation

/**========================================================================
 * @file      game.cpp
 * @author    Muaaz Bdear
 * @email     mbdear@stud.hs-bremen.de, Muaaz
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#include "game.h"
#include "welcome_scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#define ERROR -1
#define OK 0

using namespace myPong;

Game::Game()
// It initializes all member variables to default values.
    : mWindow(nullptr), mRenderer(nullptr), mFont(nullptr),
                                        // mResolution is set to {800, 600}
      wallHitSound(nullptr), paddleHitSound(nullptr), mResolution({800, 600}),
      // mHalfResolution is set to half of mResolution
      mHalfResolution({mResolution[0] / 2, mResolution[1] / 2}),
      // mPlayerScores is set to {0, 0}
      mPlayerScores({0, 0}),
      gameDB("/home/Muaaz/Schreibtisch/Letzte/myPong-main/build/assets/myPongDB 2.db3")
{
  currentUser = UserInfo();
}

Game::~Game()
{
  Mix_FreeChunk(wallHitSound);
  Mix_FreeChunk(paddleHitSound);
  TTF_CloseFont(mFont);
  SDL_DestroyWindow(mWindow);
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}

void Game::start()
{
  // initialize the SDL2 framework along with systems.
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }

  // initialize the TTF framework for the text rendering.
  if (TTF_Init() == -1)
  {
    std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
    return;
  }

  // try to create a new window for the application.
  mWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, mResolution[0],
                             mResolution[1], SDL_WINDOW_SHOWN);
  if (mWindow == nullptr)
  {
    std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }

  // try to create a new renderer for the application window.
  mRenderer = SDL_CreateRenderer(
      mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mRenderer == nullptr)
  {
    std::cerr << "Unable to create SDL renderer: " << SDL_GetError()
              << std::endl;
    return;
  }

  // initialize the font we want to use within our application.
  mFont = TTF_OpenFont("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/Lato-Italic.ttf", 20);
  if (mFont == nullptr)
  {
    std::cerr << "Unable to load a font for the application: " << TTF_GetError()
              << std::endl;
  }
  // Initialize sound effects
  // Mix_OpenAudio (frequency, format, channels, chunksize)
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  wallHitSound = Mix_LoadWAV("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/WallHit.wav");
  if (wallHitSound == nullptr)
  {
    std::cerr << "Unable to load sound effects for the application: "
              << Mix_GetError() << std::endl;
  }

  paddleHitSound = Mix_LoadWAV("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/PaddleHit.wav");
  if (paddleHitSound == nullptr)
  {
    std::cerr << "Unable to load sound effects for the application: "
              << Mix_GetError() << std::endl;
  }

  errorSound = Mix_LoadWAV("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/error.wav");
  if (errorSound == nullptr)
  {
    std::cerr << "Unable to load sound effects for the application: "
              << Mix_GetError() << std::endl;
  }

  goalSound = Mix_LoadWAV("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/goal.wav");
  if (goalSound == nullptr)
  {
    std::cerr << "Unable to load sound effects for the application: "
              << Mix_GetError() << std::endl;
  }

  SDL_Surface* icon = IMG_Load("/home/Muaaz/WiSe22_CPP_Group1/Pong/build/assets/yellowball.png");
    if (!icon)
    {
        std::cerr << "Unable to load icon: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_SetWindowIcon(mWindow, icon);


  // set the initial scene for the game.
  setScene(std::make_shared<WelcomeScene>(*this));
// This code is a while loop that runs as long as the variable "isRunning" is true.
  auto isRunning = true;
  SDL_Event event;
  while (isRunning)
  {
      while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
          case SDL_QUIT: isRunning = false; break;

          case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE && mTextInput.size()) { mTextInput.pop_back(); }
            if ((event.key.keysym.sym == SDLK_DOWN) || (event.key.keysym.sym == SDLK_UP)) { mTextInput.clear(); }
            mScene->onKeyDown(event.key);
            break;

          case SDL_KEYUP: mScene->onKeyUp(event.key); break;

          case SDL_MOUSEBUTTONDOWN: mScene->onMouseClick(event.button.button, event.motion.x, event.motion.y); break;
          /*
          case SDL_MOUSEMOTION:
            //int mouseX = event.motion.x;
            //int mouseY = event.motion.y;
            mouseCoord = "X: " + std::to_string(event.motion.x) + " Y: " + std::to_string(event.motion.y);
            SDL_SetWindowTitle(mWindow, mouseCoord.c_str());
            break;
          */
          case SDL_TEXTINPUT:
            mTextInput += event.text.text;
            mScene->onTextInpt(mTextInput);
            break;
      }
    }


    mScene->onUpdate();

    // clear the rendering context with the black color.
    // 0xff -> 255 , 0x00 -> 0
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    // turn the renderer draw color to white.
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);

    // render scene stuff into the buffer.
    mScene->onDraw(*mRenderer);

    SDL_RenderPresent(mRenderer);
  }
}

//This function "setScene" sets a new scene, it takes a pointer to a scene object as an input.
void Game::setScene(ScenePtr scene)
{
  // skip the null scene assignment.
  if (scene == nullptr)
  {
    std::cerr << "Unable to set null as the active scene!" << std::endl;
    return;
  }

  // tell old scene (if any) that we are going to exit from it.
  if (mScene)
  {
    mScene->onExit();
  }

  // assign and enter the new scene.
  mScene = scene;
  mScene->onEnter();
}

SDL_Texture *Game::createText(const std::string &text)
{
  // create a surface which contains the desired text.
  SDL_Color color{0x87, 0x00, 0x20, 0xff};
  auto surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
  if (surface == nullptr)
  {
    std::cerr << "Unable to create a surface with a text: " << TTF_GetError()
              << std::endl;
    return nullptr;
  }

  // create a texture from the text surface.
  auto texture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr)
  {
    std::cerr << "Unable to create texture from a text surface: "
              << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}
// This function creates an image using SDL_Texture and loads it using IMG_LoadTexture.
SDL_Texture *Game::createImage(const char *fileName)
{
// It uses the renderer (mRenderer) to load the image from the fileName.
  SDL_Texture *texture = IMG_LoadTexture(mRenderer, fileName);
  // If the image fails to load, it will return nullptr
  if (texture == nullptr)
  {
    // An error message is displayed
    std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError()
              << std::endl;
    // Function return nullptr
    return nullptr;
  }

  /*
  SDL_FreeSurface(img);
  */
  return texture;
}
// This function "playSoundEffect" plays a sound effect based
// on the index of the sound clip provided as input.
void Game::playSoundEffect(SoundClips soundClip)
{
    switch (soundClip)
    {
        case HIT_PADDLE:
        Mix_PlayChannel(-1, paddleHitSound, 0);
        break;
        case HIT_WALL:
        Mix_PlayChannel(-1, wallHitSound, 0);
        break;
        case GOAL:
        Mix_PlayChannel(-1, goalSound, 0);
        break;
        default:
        Mix_PlayChannel(-1, errorSound, 0);
        break;
    }
}
bool Game::checkUser(const std::string desiredUserName, const std::string desiredUserPassword)
{
  bool isFound = gameDB.checkUser(desiredUserName, desiredUserPassword);
  if (isFound) { gameDB.getFirstUser(currentUser); }
  return isFound;
}
int Game::ShowDialogBox(const std::string &title, const std::string &message)
{
  int buttonid = -1;

  const SDL_MessageBoxButtonData buttons[] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "No" },
  };

  const SDL_MessageBoxData messageboxdata = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL,                       /* .window */
    title.c_str(),              /* .title */
    message.c_str(),            /* .message */
    SDL_arraysize(buttons),     /* .numbuttons */
    buttons,                    /* .buttons */
    NULL                        /* .colorScheme */
  };

  int ret = SDL_ShowMessageBox(&messageboxdata, &buttonid);
  //if (!ret) { return ret; }
  return buttonid;
}

int Game::ShowSimpleDialogBox(const std::string &title, const std::string &message, const int &dialogType)
{
  Uint32 flags[3] = { SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, SDL_MESSAGEBOX_INFORMATION };
  return SDL_ShowSimpleMessageBox(flags[dialogType], title.c_str(), message.c_str(), mWindow);
}
