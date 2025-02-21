#include <iostream>
#include "SDL2/SDL.h"

#include "gg2d/Game.h"

const int WIN_W = 1040;
const int WIN_H = 800;

int main(int argc, char *argv[])
{

  TheGame::Instance()->run("gg2d demo", WIN_W, WIN_H);

  //...
  return 0;
}