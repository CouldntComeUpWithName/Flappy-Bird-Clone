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
  std::srand(std::time(nullptr));
  
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
     load_texture(m_renderer, "../../flappy-game/res/textures/Birds.png")).get();
  
  m_background.sprite.texture = texture_manager::load(texture_type::VANILLA_BACKGROUND,
    load_texture(m_renderer, "../../flappy-game/res/textures/default-bg-day.png")).get();
  
  m_pipeline.pipe_texture(texture_manager::load(texture_type::VANILLA_PIPE,
      load_texture(m_renderer, "../../flappy-game/res/textures/pipe-green.png")));
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
  while (m_running) 
  {
    float fixed_timestep = 1.f / 60;
    poll_events();
    update(fixed_timestep);
    render();
  }
}

void flappy::game::poll_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type) 
    {
    case SDL_EVENT_QUIT:
      m_running = false;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      m_state = state::gameplay;
      flap();
      break;
    case SDL_EVENT_KEY_DOWN:
    {
      if (event.key.scancode == SDL_SCANCODE_D)
      {
        m_toggle_db_info ^= true;
      }
      break;
    }
    case SDL_EVENT_KEY_UP:
      break;
    default:
      break;
    }
  }
}

void flappy::game::update(float dt)
{
  switch(m_state) 
  {
    using enum state;
  case waiting:
    break;
  case gameplay:
    update_gameplay(dt);
    break;
  case game_over:
    m_pipeline.reset();
    m_state = waiting;
    break;
  }
}

void flappy::game::update_gameplay(float dt)
{
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
      m_state = state::game_over;
    }
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
  
  m_pipeline.render(m_renderer);
  
  SDL_RenderTexture(m_renderer.get(), m_bird.sprite.texture, &m_bird.sprite.rect, &dest);
  
  if(m_state == state::game_over)
  {
    //TODO: render game over menu
  }

  if (m_toggle_db_info)
  {
    render_deb_info();
  }
  
  // draw the score after
  
  SDL_RenderPresent(m_renderer.get());
}

void flappy::game::render_deb_info()
{
  SDL_Color color{ 255, 0, 255, 255 };
  SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);

  SDL_FRect bird_boundary = {
    m_bird.position.x,
    m_bird.position.y,
    m_bird.collider.w,
    m_bird.collider.h,
  };
  
  SDL_RenderRect(m_renderer.get(), &bird_boundary);
  
  for (const auto& [lower, upper] : m_pipeline)
  {
    SDL_RenderRect(m_renderer.get(), &lower.collider);
    SDL_RenderRect(m_renderer.get(), &upper.collider);
  }

  if(m_state == state::game_over)
  {
    //TODO: render the button clickable areas
  }
  
}

void flappy::game::flap()
{
  m_bird_up_force = 10.f;
}

flappy::game::~game()
{
  SDL_Quit(); 
}
