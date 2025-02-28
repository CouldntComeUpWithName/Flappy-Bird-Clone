#pragma once
#include "gfx.hpp"
#include "entity.hpp"
#include <vector>

namespace flappy
{
  class pipe_line
  {
    using pipe_pair = std::pair<pipe, pipe>;
  public:
    pipe_line() = default;

    void init();
    void reset();

    void update(float);
    void render(const sdl::renderer&);
    
    void section_count(uint32_t n) { m_nsections = n; }
    void entrance_height(pixel_t height) { m_entrance_height = height; }
    void screen_space(const SDL_FRect& space) { m_screen_space = space; }

    void pipe_texture(sdl::texture& t) { m_common.texture = &t; }
    void pipe_size(const SDL_FRect& rect) { m_common.size = rect; }
  
    auto begin() { return m_pipeline.begin(); }
    auto end() { return m_pipeline.end(); }
  
  private:
    void gen_next_pair();
    void gen_next_pair_at(float x);

    void render_pipe(const sdl::renderer&, const pipe&);
    void render_pipe_flipped(const sdl::renderer&, const pipe& pipe);

  private: 
    struct pipe_common 
    {
      sdl::texture* texture = nullptr;
      SDL_FRect        size = { .x = 0, .y = 0, .w = 100, .h = 500 };
    };

  private:
    uint32_t m_section_fixed_step  = 200u;
    uint32_t m_initial_xoffset     = 1000u;
    uint32_t m_pipe_hmin           = 100u;
    pixel_t m_entrance_height = 200u;
    uint32_t m_nsections      = 4;
    uint64_t m_first          = 0;
    SDL_FRect m_screen_space  = {};
    pipe_common m_common      = {};
    std::vector<pipe_pair> m_pipeline;
  };
}