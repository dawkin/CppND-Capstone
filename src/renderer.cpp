#include "renderer.h"
#include <iostream>
#include <string>
#include <cmath>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  SDL_ShowCursor(0);

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Spaceship &spaceship, std::vector<Missile> &missiles, Mouse &mouse, Asteroid &asteroid) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // aimcross rendering
    mouse.loadTexture(sdl_renderer);
    SDL_Rect dest_aimcross = mouse.getRectPos();
    SDL_QueryTexture(mouse.getTexture(), NULL, NULL, &dest_aimcross.w, &dest_aimcross.h);
    SDL_RenderCopyEx(sdl_renderer, mouse.getTexture(), NULL, &dest_aimcross, 90.0, NULL, SDL_FLIP_NONE);

    // missiles rendering
    for (Missile &m: missiles)
    {
        m.loadTexture(sdl_renderer);
        SDL_Rect dest_m = m.getRectPos();
        SDL_QueryTexture(m.getTexture(), NULL, NULL, &dest_m.w, &dest_m.h);
        SDL_RenderCopyEx(sdl_renderer, m.getTexture(), NULL, &dest_m, m.getAngle(), NULL, SDL_FLIP_NONE);
    }
    // spaceship rendering
    spaceship.loadTexture(sdl_renderer);
    SDL_Rect dest_spaceship = spaceship.getRectPos();
    SDL_QueryTexture(spaceship.getTexture(), NULL, NULL, &dest_spaceship.w, &dest_spaceship.h);
    SDL_RenderCopyEx(sdl_renderer, spaceship.getTexture(), NULL, &dest_spaceship, spaceship.getAngle(), NULL, SDL_FLIP_NONE);

    // asteroid rendering
    asteroid.loadTexture(sdl_renderer);
    SDL_Rect dest_asteroid = asteroid.getRectPos();
    SDL_QueryTexture(asteroid.getTexture(), NULL, NULL, &dest_asteroid.w, &dest_asteroid.h);
    SDL_RenderCopy(sdl_renderer, asteroid.getTexture(), NULL, &dest_asteroid);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Asteroid Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
