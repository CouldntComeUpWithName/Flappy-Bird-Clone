#pragma once
#include "gfx.hpp"
#include "entity.hpp"
#include "pipe_line.hpp"

namespace flappy
{
  class game
  {
  public:
    game();

    void run();

  private:
    void load_assets();
    void init();

    void poll_events();
    void update(float);
    void render();
    
    void render_deb_info();

  public:
    ~game();

  private:
    struct app_meta
    {
      uint32_t screen_width  = 600;
      uint32_t screen_height = 800;
      std::string title = "flappy-clone";
    };

    enum class state
    {
      waiting,
      gameplay,
      game_over,
    };
    
  private:
    state m_state = state::waiting;
    
    bool m_running = { true };

    bool m_toggle_db_info = { false };

    uint32_t m_score = { 0U };
    
    sdl::window m_main_window = { nullptr };
    sdl::renderer m_renderer  = { nullptr };
    
    bird m_bird             = {};
    renderable m_background = {};
    
    app_meta m_appdata = {};
    pipe_line m_pipeline; 
  };

};