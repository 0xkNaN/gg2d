#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
private:
  Game() {}

  static Game *s_pInstance;

  bool m_bRunning;

public:
  ~Game() {}

  static Game *Instance()
  {
    if (s_pInstance == 0)
      s_pInstance = new Game();
    return s_pInstance;
  }

  bool init(const char *title, int windowW, int windowH);

  void events();
  void update();
  void render();

  void run(const char *title, int windowW, int windowH);

  bool running() { return m_bRunning; }

  void clean();
};

typedef Game TheGame;