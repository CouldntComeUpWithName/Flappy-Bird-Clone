#pragma once

#include "core.hpp"
#include <SDL3/SDL.h>

namespace flappy
{
  namespace sdl
  {
    struct texture_deleter 
    {
      void operator()(auto* ptr) { SDL_DestroyTexture(ptr); }
    };
    
    struct window_deleter 
    {
      void operator()(auto* ptr){ SDL_DestroyWindow(ptr); }
    };
    
    struct renderer_deleter 
    {
      void operator()(auto* ptr){ SDL_DestroyRenderer(ptr); }
    };
    
    struct surface_deleter 
    {
      void operator()(auto* ptr){ SDL_DestroySurface(ptr); }
    };

    using texture  = uptr<SDL_Texture, texture_deleter>;
    using window   = uptr<SDL_Window, window_deleter>;
    using renderer = uptr<SDL_Renderer, renderer_deleter>;
    using surface  = uptr<SDL_Surface, surface_deleter>;
  }
  
  struct sprite_sheet
  {
    SDL_Texture* texture;
    SDL_FRect rect;
  };
  
  sdl::texture load_texture(const sdl::renderer&, const std::string&);
}
