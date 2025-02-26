#include "pipe_line.hpp"
#include <iostream>

void flappy::pipe_line::init()
{
  std::srand(std::time(nullptr));

  m_pipeline.resize(m_nsections);

  for(int i = 0; i < m_nsections; i++)
  {
    auto& [lower_pipe, upper_pipe] = gen_next_pair();
    
    lower_pipe.collider.w = m_common.size.w;
    lower_pipe.collider.h = m_common.size.h;

    upper_pipe.collider.w = m_common.size.w;
    upper_pipe.collider.h = m_common.size.h;
  }
}

void flappy::pipe_line::update(float dt)
{
  auto& lower_pipe = m_pipeline[m_first].first;
  
  if (lower_pipe.position.x + m_common.size.w < 0)
  {
    auto& [lower, upper] = gen_next_pair();
    
    lower.collider.w = m_common.size.w;
    lower.collider.h = m_common.size.h;

    upper.collider.w = m_common.size.w;
    upper.collider.h = m_common.size.h;
    
  }
}

void flappy::pipe_line::render(const sdl::renderer& renderer)
{
  if(m_common.texture)
  {
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 255, 255);
    
    for(const auto& [lower_pipe, upper_pipe] : m_pipeline)
    {
      render_pipe(renderer, lower_pipe);
      
      render_pipe_flipped(renderer, upper_pipe);
    }
  }
}

flappy::pipe_line::pipe_pair& flappy::pipe_line::gen_next_pair()
{
  const uint32_t section_fixed_step = 200;
  constexpr uint32_t pipe_hmin = 100;
  static auto num = 0;
  
  // takes the first pipe, makes it the last one
  auto& [lower_pipe, upper_pipe] = m_pipeline[m_first];
  
  auto last_idx = (m_first + m_nsections - 1) % m_nsections;
  auto lastx = m_pipeline[last_idx].first.position.x;

  lower_pipe.position.x = lastx + m_common.size.w + section_fixed_step;
  lower_pipe.position.y = std::rand() % (((int)m_screen_space.h - pipe_hmin) - (m_entrance_height + pipe_hmin + 1)) + m_entrance_height + pipe_hmin + 1;
  
  lower_pipe.collider.x = lower_pipe.position.x;
  lower_pipe.collider.y = lower_pipe.position.y;

  upper_pipe.position.x = lower_pipe.position.x;
  
  upper_pipe.position.y = lower_pipe.position.y - m_entrance_height - m_common.size.h;

  upper_pipe.collider.x = upper_pipe.position.x;
  upper_pipe.collider.y = upper_pipe.position.y;

  auto idx = m_first;

  m_first = ((m_first + 1) % m_nsections);
  return m_pipeline[idx];
}

void flappy::pipe_line::render_pipe(const sdl::renderer& renderer, const pipe& pipe)
{
  SDL_FRect dest {
    .x = pipe.position.x,
    .y = pipe.position.y,
    .w = m_common.size.w,
    .h = m_common.size.h
  };

  SDL_RenderTexture(renderer.get(), m_common.texture->get(), nullptr, &dest);
}

void flappy::pipe_line::render_pipe_flipped(const sdl::renderer& renderer, const pipe& pipe)
{
  SDL_FRect dest {
    .x = pipe.position.x,
    .y = pipe.position.y,
    .w = m_common.size.w,
    .h = m_common.size.h
  };
  
  SDL_FPoint center = {0.f, 0.f}; 

  SDL_RenderTextureRotated(renderer.get(), m_common.texture->get(), nullptr, 
    &dest, 0.0, &center, SDL_FLIP_VERTICAL);
}
