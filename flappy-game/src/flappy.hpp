#pragma once
#include "core.hpp"
#include "gfx.hpp"
#include <SDL3/SDL.h>
#include <string>
#include "entity.hpp"

namespace flappy
{
  class game
  {
  public:
    game();

    void run();

  private:
    void load_assets();

    void poll_events();
    void update(float);
    void render();

  public:
    ~game();

  private:
    struct app_meta
    {
      uint32_t screen_width = 600;
      uint32_t screen_height = 800;
      std::string title = "flappy";
    };

  private:
    bool m_running   = { true };
    bool m_paused    = { false };
    uint32_t m_score = { 0U };
    
    SDL_Window* m_main_window = { nullptr };
    SDL_Renderer* m_renderer  = { nullptr };

    SDL_Texture* m_pipe = { nullptr };

    std::vector<int> m_pipes;
    entity m_bird       = {};
    entity m_background = {};
    
    app_meta m_appdata = {};
  };

};