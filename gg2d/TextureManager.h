#pragma once

#include <iostream>
#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
public:
  ~TextureManager() {}

  static TextureManager *Instance()
  {
    if (s_pInstance == 0)
      s_pInstance = new TextureManager();
    return s_pInstance;
  }

  bool load(SDL_Renderer *renderer, std::string id, std::string src);

  void draw(
      SDL_Renderer *renderer,
      std::string id,
      int x, int y, int w, int h,
      int currR = 0, int currF = 0,
      SDL_RendererFlip flip = SDL_FLIP_NONE);

  void drawTile() {}

  void clearTexture(std::string id) {}

  std::map<std::string, SDL_Texture *> textureMap() { return m_textureMap; }

private:
  TextureManager() {}
  static TextureManager *s_pInstance;
  std::map<std::string, SDL_Texture *> m_textureMap;
};

typedef TextureManager TheTextureManager;