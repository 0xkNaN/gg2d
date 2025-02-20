#include <iostream>
#include "SDL2/SDL.h"
#include "gg2d/Game.h"

const int WIN_W = 1040;
const int WIN_H = 800;

Game *g_game;

int main(int argc, char *argv[])
{
  g_game = new Game();

  //? Init
  g_game->init("gg2d demo", WIN_W, WIN_H);

  //? Game Loop
  while (g_game->running())
  {
    g_game->events();
    g_game->update();
    g_game->render();
  }

  //? Cleanup
  g_game->clean();

  //...
  return 0;
}