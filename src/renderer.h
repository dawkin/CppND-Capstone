#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "spaceship.h"
#include "missile.h"
#include "mouse.h"
#include "asteroid.h"
#include <vector>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Spaceship &spaceship, std::vector<Missile> &missiles, Mouse &mouse, Asteroid &asteroid);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif