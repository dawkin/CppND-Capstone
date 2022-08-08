#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "asteroid.h"
#include "missile.h"
#include "mouse.h"


class Game {
public:
    Game(std::size_t screen_width, std::size_t screen_height);
    void Run(std::size_t target_frame_duration);
    int GetScore() const;

private:
    // Element of the game
    Spaceship _spaceship;
    Asteroid _asteroid;
    std::vector<Missile> _missiles;
    Mouse _mouse;

    std::size_t screen_width;
    std::size_t screen_height;
    std::mutex _space_object_mutex;
    std::mutex _running_mutex;
    int score{0};

    /* Private methods */
    void Render(Renderer &renderer, std::size_t target_frame_duration, bool &running);
    void Update(Controller &controller, bool &running);
    void collisionCheck(bool &running);

    template<typename T1, typename T2>
    bool collision(T1 a, T2 b);
};

#endif