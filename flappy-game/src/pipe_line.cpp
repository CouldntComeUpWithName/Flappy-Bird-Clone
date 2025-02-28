#include "pipe_line.hpp"
#include <iostream>

void flappy::pipe_line::init()
{
  m_pipeline.resize(m_nsections, {});
  
  for(int i = 0; i < m_nsections; i++)
  {
    float x = i * (m_common.size.w + m_section_fixed_step) + m_initial_xoffset;
    gen_next_pair_at(x);
  }
}

void flappy::pipe_line::reset()
{
  m_first = 0;
  init();
}

void flappy::pipe_line::update(float dt)
{
  auto& lower_pipe = m_pipeline[m_first].first;
  
  if (lower_pipe.position.x + m_common.size.w < 0)
  {
    gen_next_pair();
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

void flappy::pipe_line::gen_next_pair()
{
  auto last_idx = (m_first + m_nsections - 1) % m_nsections;
  auto lastx = m_pipeline[last_idx].first.position.x;
  
  float x = lastx + m_common.size.w + m_section_fixed_step;
  gen_next_pair_at(x);
}

void flappy::pipe_line::gen_next_pair_at(float x)
{
  auto& [lower_pipe, upper_pipe] = m_pipeline[m_first];
  
  lower_pipe.position.x = x;
  lower_pipe.position.y = std::rand() % (((int)m_screen_space.h - m_pipe_hmin) - 
    (m_entrance_height + m_pipe_hmin + 1)) + m_entrance_height + m_pipe_hmin + 1;
  
  lower_pipe.collider = {
    .x = lower_pipe.position.x,
    .y = lower_pipe.position.y,
    .w = m_common.size.w,
    .h = m_common.size.h
  };

  upper_pipe.position.x = lower_pipe.position.x;
  upper_pipe.position.y = lower_pipe.position.y - m_entrance_height - m_common.size.h;

  upper_pipe.collider = {
    .x = upper_pipe.position.x,
    .y = upper_pipe.position.y,
    .w = m_common.size.w,
    .h = m_common.size.h
  };

  m_first = ((m_first + 1) % m_nsections);
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
