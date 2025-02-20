#include "TextureManager.h"

TextureManager *TextureManager::s_pInstance = nullptr;

bool TextureManager::load(SDL_Renderer *renderer, std::string id, std::string src)
{
  SDL_Surface *surface = IMG_Load(src.c_str());
  if (surface == 0)
  {
    return false;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (texture == 0)
  {
    return false;
  }

  std::cout << id << " :: " << texture << std::endl;

  //...
  m_textureMap[id] = texture;
  return true;
}

void TextureManager::draw(
    SDL_Renderer *renderer,
    std::string id,
    int x, int y, int w, int h,
    int currR, int currF,
    SDL_RendererFlip flip)
{
  //? Rect x, y, w, h
  SDL_Rect srect = {w * currF, h * currR, w, h};
  SDL_Rect drect = {x, y, w, h};

  // std::cout << id << " :: " << m_textureMap[id] << std::endl;

  //? Draw the texture
  SDL_RenderCopyEx(renderer, m_textureMap[id], &srect, &drect, 0, 0, flip);
}