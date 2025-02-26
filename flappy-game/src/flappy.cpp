#include "flappy.hpp"
#include "physics.hpp"

#include <chrono>
#include <iostream>

#include "assets.hpp"
#include "asset_manager.hpp"

namespace flappy
{
  using texture_manager = asset_manager<texture_type, sdl::texture>;
}

flappy::game::game()
{
  assert(SDL_Init(SDL_INIT_VIDEO));
  
  m_main_window = sdl::window { 
    SDL_CreateWindow(m_appdata.title.c_str(), m_appdata.screen_width, m_appdata.screen_height, 0) 
  };
  
  assert(m_main_window && "SDL_APP_FAILURE");

  m_renderer = sdl::renderer { 
    SDL_CreateRenderer(m_main_window.get(), nullptr)
  };

  assert(m_renderer && "Uninitialized renderer");

  load_assets();
  
  init();
}

void flappy::game::load_assets()
{
  m_bird.sprite.texture = texture_manager::load(texture_type::BIRD_SHEET, 
     load_texture(m_renderer, "../../flappy-game/res/Birds.png")).get();
  
  m_background.sprite.texture = texture_manager::load(texture_type::VANILLA_BACKGROUND,
    load_texture(m_renderer, "../../flappy-game/res/default-bg-day.png")).get();
  
  m_pipeline.pipe_texture(texture_manager::load(texture_type::VANILLA_PIPE,
      load_texture(m_renderer, "../../flappy-game/res/pipe-green.png")));
}

void flappy::game::init()
{
  m_bird.sprite.rect = { .x = 0, .y = 3, .w = 16, .h = 16 };
  m_bird.velocity = { 0.5f, 1.f };
  
  m_bird.position = { 
    (m_appdata.screen_width - m_bird.sprite.rect.w) / 2.f, 
    (m_appdata.screen_height - m_bird.sprite.rect.h) / 2.f 
  };
  
  m_bird.collider = { m_bird.position.x, m_bird.position.y, 16 * 4, 12 * 4 };

  SDL_FRect screen_space{
    .x = 0.f,
    .y = 0.f,
    .w = (float)m_appdata.screen_width,
    .h = (float)m_appdata.screen_height
  };

  m_pipeline.screen_space(screen_space);
  m_pipeline.init();
}

void flappy::game::run()
{
  SDL_FRect r1 = { 100.0f, 100.0f, 50.0f, 50.0f };
  SDL_FRect r2 = { 120.0f, 120.0f, 50.0f, 50.0f };

  while (m_running) 
  {
    float dt = 1.f / 60;
    poll_events();
    update(dt);
    render();
  }
}

void flappy::game::poll_events()
{
  // TODO: probably move event handling here
}

uint8_t draw_color[4] = {};

void flappy::game::update(float dt)
{
  static float up_force = 0.f;
  static bool flapping = false;
  
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type) 
    {
    case SDL_EVENT_QUIT:
      m_running = false;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      flapping = true;
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      break;
    case SDL_EVENT_KEY_DOWN:
    {
      if (event.key.scancode == SDL_SCANCODE_ESCAPE)
      {
        m_paused = !m_paused;
      }
      if (event.key.scancode == SDL_SCANCODE_D)
      {
        m_toggle_db_info ^= true; // showing off
      }
      break;
    }
    case SDL_EVENT_KEY_UP:
      break;
    default:
      break;
    }
  }

  if (!m_paused)
  {
    // move the environment by x-axis with -m_bird.velocity.x component
    // so that it gives the impression that the bird is actually moving

    m_pipeline.update(dt);

    for(auto& [lower_pipe, upper_pipe] : m_pipeline)
    {
      lower_pipe.position.x += (-m_bird.velocity.x) * dt;
      upper_pipe.position.x += (-m_bird.velocity.x) * dt;
      
      lower_pipe.collider.x = lower_pipe.position.x;
      upper_pipe.collider.x = upper_pipe.position.x;
    }
    
    for (auto& [lower_pipe, upper_pipe] : m_pipeline)
    {
      if (physics::collides(m_bird.collider, lower_pipe.collider)
        || physics::collides(m_bird.collider, upper_pipe.collider))
      {
        m_running = false;
        // TODO: implement game over
      }
    }

  //score update

  }
}

void flappy::game::render()
{
  SDL_RenderClear(m_renderer.get());
  
  float aspect_ratio = m_appdata.screen_width / (float)m_appdata.screen_height;

  auto dest = SDL_FRect { 
    .x = m_bird.position.x, 
    .y = m_bird.position.y, 
    .w = (float)m_appdata.screen_width * 0.1f, 
    .h = (float)m_appdata.screen_height * 0.1f * aspect_ratio
  };

  SDL_RenderTexture(m_renderer.get(), m_background.sprite.texture, nullptr, nullptr);
  
  SDL_RenderTexture(m_renderer.get(), m_bird.sprite.texture, &m_bird.sprite.rect, &dest);

  m_pipeline.render(m_renderer);
  
  if (m_toggle_db_info)
  {
    render_deb_info();
  }
  
  if (m_paused)
  {
    // draw the pause menu here
  }
  // draw the score after
  
  

  SDL_RenderPresent(m_renderer.get());
}

void flappy::game::render_deb_info()
{
  
}


flappy::game::~game()
{
  SDL_Quit(); 
}
