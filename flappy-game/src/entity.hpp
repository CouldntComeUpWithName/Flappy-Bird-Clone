#pragma once
#include "core.hpp"
#include "gfx.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

namespace flappy
{
  // this is so fucked up, rearrangement is needed immediately
  
  // comprises the all essential components
  struct basic_entity
  {
    glm::vec2 position;
    SDL_FRect collider;
  };

  struct movable
  {
    glm::vec2 velocity;
  };

  struct renderable
  {
    sprite_sheet sprite;
  };

  struct bird 
  : basic_entity, movable, renderable
  {
    
  };

  struct pipe 
  : basic_entity
  {

  };

}