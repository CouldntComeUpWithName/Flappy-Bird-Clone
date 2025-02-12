#include "gfx.hpp"
#include <stb_image.h>

namespace flappy
{
  sdl::texture load_texture(const sdl::renderer& renderer, const std::string& filepath)
  {
    int width    = {};
    int height   = {};
    int channels = {};
    auto* image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
  
    assert(image && "Image loading has failed");
  
    sdl::surface surface { 
      SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, image, width * channels) 
    };
    
    sdl::texture texture { 
      SDL_CreateTextureFromSurface(renderer.get(), surface.get())
    };

    SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
  
    stbi_image_free(image);

    return texture;
  }
}


