#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
public:
  Game() {}
  ~Game() {}

  bool init(const char *title, int windowW, int windowH);

  void events();
  void update();
  void render();

  void clean();

  bool running() { return m_bRunning; }

private:
  bool m_bRunning;
  // TextureManager *textureManager;
};