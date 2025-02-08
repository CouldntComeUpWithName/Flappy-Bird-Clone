#pragma once
#include "core.hpp"
#include "gfx.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

namespace flappy
{
  namespace detail
  {
    struct entity_components
    {
      sprite_sheet sprite;
      glm::vec2 velocity;
      glm::vec2 position;
      SDL_FRect collider;
    };
  }
  
  using entity_id = uint64_t;
  using entity = detail::entity_components;
}