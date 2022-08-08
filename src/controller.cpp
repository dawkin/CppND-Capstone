#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Spaceship &spaceship, std::vector<Missile> &missiles, Mouse &mouse) {
    SDL_Event e;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse.definePosition(mouse_x, mouse_y);
    spaceship.setAngle(mouse_x, mouse_y);
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            Missile missile{};
            missile.setSpeed(300.0,spaceship.getAngle());
            missile.setAngle(spaceship.getAngle());
            Coordinate missile_init_pos = spaceship.getShootingPoint();
            missile.definePosition((int) missile_init_pos.x, (int) missile_init_pos.y);
            missiles.push_back(missile);
        }
    }
}