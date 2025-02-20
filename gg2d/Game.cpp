#include <iostream>
#include <map>

#include "Game.h"

#include "TextureManager.h"

SDL_Window *pWindow = 0;
SDL_Renderer *pRenderer = 0;

int tmpCurrentSpriteFrame;
int tmpPositionXSprite;

bool Game::init(const char *title, int windowW, int windowH)
{
  //? Init SDL
  int ini = SDL_Init(SDL_INIT_EVERYTHING);
  if (ini < 0)
  {
    std::cout << "SDL init error :: " << SDL_GetError() << std::endl;
    return 1;
  }

  //? Create Window
  pWindow = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      windowW,
      windowH,
      SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_RESIZABLE);
  if (pWindow == 0)
  {
    std::cout << "SDL window error :: " << SDL_GetError() << std::endl;
    return 1;
  }

  //? Create Renderer
  pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
  if (pRenderer == 0)
  {
    std::cout << "SDL error :: " << SDL_GetError() << std::endl;
    return 1;
  }

  //? Load Textures
  TheTextureManager::Instance()->load(pRenderer, "rider", "assets/rider.bmp");
  TheTextureManager::Instance()->load(pRenderer, "animate", "assets/animate-alpha.png");

  //...
  m_bRunning = true;
  return 0;
}

void Game::events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      m_bRunning = false;
      break;

    case SDL_MOUSEMOTION:
      // SDL_Log("Mouse [%d, %d]", event.motion.x, event.motion.y);
      break;

    default:
      break;
    }
  }
}

void Game::update()
{
  tmpPositionXSprite = (int)(SDL_GetTicks64() / 10);
  tmpCurrentSpriteFrame = (int)((SDL_GetTicks64() / 100) % 6);
}

void Game::render()
{
  //? Clear Renderer
  SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(pRenderer);

  //? Draw textures
  TheTextureManager::Instance()->draw(pRenderer, "rider", 0, 0, 123, 87);
  TheTextureManager::Instance()->draw(pRenderer, "animate", tmpPositionXSprite, 120, 128, 82, 0, tmpCurrentSpriteFrame);

  //? Swap the thing
  SDL_RenderPresent(pRenderer);
}

void Game::clean()
{
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
  SDL_Quit();
}
