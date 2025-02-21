#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"

#include "TextureManager.h"

Game *Game::s_pInstance = nullptr;

SDL_Window *pWindow = 0;
SDL_Renderer *pRenderer = 0;

int jackPosX = 0;
int jackPosY = 100;
int jackFrame;

int mousePosX;
int mousePosY;

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
  TheTextureManager::Instance()->load(pRenderer, "jack", "assets/jack.png");

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
      mousePosX = event.motion.x;
      mousePosY = event.motion.y;
      // SDL_Log("Mouse [%d, %d]", event.motion.x, event.motion.y);
      break;

    default:
      break;
    }
  }
}

void Game::update()
{
  //? Calculate distance from Jack to Mouse
  //? Distance sqrt[(x2 - x1)**2 + (y2 - y1)**2]
  glm::vec2 jackPos(jackPosX, jackPosY);
  glm::vec2 MousePos(mousePosX, mousePosY);
  float distance = glm::distance(jackPos, MousePos);
  // std::cout << "Distance  :: " << distance << std::endl;

  //? Check if Mouse/Jack collision
  bool isCollided = distance < 100;

  std::cout << "jackPosX  :: " << jackPosX << std::endl;

  //? Update Positions
  if (!isCollided)
  {
    jackPosX = (int)(SDL_GetTicks64() / 30);
    jackFrame = (int)((SDL_GetTicks64() / 100) % 8);
  }
}

void Game::render()
{
  //? Clear Renderer
  SDL_SetRenderDrawColor(pRenderer, 86, 125, 70, 255);
  SDL_RenderClear(pRenderer);

  //? Draw textures
  TheTextureManager::Instance()->draw(
      pRenderer, "jack", jackPosX, jackPosY, 669, 569, 0.3, 0, jackFrame); // 5352 × 569 [669]

  //? Draw Jack Rect
  // SDL_Rect drect = {jackPosX, jackPosY, int(669 * 0.3), int(569 * 0.3)};
  // SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
  // SDL_RenderDrawRect(pRenderer, &drect);

  //? Draw line from mouse to Jack
  // SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
  // SDL_RenderDrawLine(pRenderer, mousePosX, mousePosY, jackPosX, jackPosY);

  //? Swap the thing
  SDL_RenderPresent(pRenderer);
}

void Game::clean()
{
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
  SDL_Quit();
}

void Game::run(const char *title, int windowW, int windowH)
{
  //? Init
  Game::s_pInstance->init(title, windowW, windowH);

  //? Game Loop
  while (Game::s_pInstance->running())
  {
    Game::s_pInstance->events();
    Game::s_pInstance->update();
    Game::s_pInstance->render();
  }

  //? Cleanup
  Game::s_pInstance->clean();
}
