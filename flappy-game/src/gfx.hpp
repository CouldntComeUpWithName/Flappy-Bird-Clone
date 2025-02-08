#pragma once
#include <SDL3/SDL.h>

struct sprite_sheet
{
  SDL_Texture* texture;
  SDL_FRect rect;
};