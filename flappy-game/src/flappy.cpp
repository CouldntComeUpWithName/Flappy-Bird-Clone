#include "flappy.hpp"

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

  m_renderer = sdl::renderer{ SDL_CreateRenderer(m_main_window.get(), nullptr) };

  assert(m_renderer && "Uninitialized renderer");

  load_assets();
}

void flappy::game::run()
{
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
      std::cout << "flap...\n";
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      std::cout << "fall...\n";
      break;
    case SDL_EVENT_KEY_DOWN:
    {
      if (event.key.scancode == SDL_SCANCODE_ESCAPE)
      {
        m_paused = !m_paused;
      }
      break;
    }
    case SDL_EVENT_KEY_UP:
      break;
    default:
      break;
    }
  }
  
  static float f_acceleration = 0.f;
  constexpr float f_gravity = 2.f;

  if (!m_paused)
  {

  // move the environment by x-axis with -m_bird.velocity.x component
  // so that it gives the impression that the bird is actually moving

  // collisions
  //score update

  }
}

void flappy::game::render()
{
  SDL_RenderClear(m_renderer.get());

  auto dest = SDL_FRect{ .x = m_bird.position.x, .y = m_bird.position.y, .w = m_appdata.screen_width * 0.10f, .h = m_appdata.screen_width * 0.10f };

  SDL_RenderTexture(m_renderer.get(), m_background.sprite.texture, nullptr, nullptr);

  SDL_RenderTexture(m_renderer.get(), m_bird.sprite.texture, &m_bird.sprite.rect, &dest);

  if (m_paused)
  {
    // draw the pause menu here
  }
  // draw the score after

  SDL_RenderPresent(m_renderer.get());
}

void flappy::game::load_assets()
{
  m_bird.sprite.texture = texture_manager::load(texture_type::BIRD_SHEET, 
     load_texture(m_renderer, "../../flappy-game/res/Birds.png")).get();
  
  m_background.sprite.texture = texture_manager::load(texture_type::VANILLA_BACKGROUND,
    load_texture(m_renderer, "../../flappy-game/res/default-bg-day.png")).get();

  m_bird.sprite.rect = { .x = 0, .y = 0, .w = 16, .h = 16 };
  m_bird.velocity = { 1.f, 1.f };
  m_bird.position = { (m_appdata.screen_width - (m_bird.sprite.rect.w * 5)) / 2.f, (m_appdata.screen_height - m_bird.sprite.rect.h) / 2.f };
}

flappy::game::~game()
{
  SDL_Quit(); 
}
