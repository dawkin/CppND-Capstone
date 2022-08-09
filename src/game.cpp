#include "game.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height):
      screen_height(screen_height),
      screen_width(screen_width) {}

void Game::Run(std::size_t target_frame_duration)
{
    /*
     * Start a new game with two different thread one for the Model and Controler
     * another one for the View
     */
  // Init the spaceship's position at the middle of the frame
  Controller controller;
  Renderer renderer(screen_width, screen_height);
  _spaceship.definePosition(screen_width/2, screen_height/2);
  bool running = true;
  std::thread update(&Game::Update, this, std::ref(controller), std::ref(running));
  std::thread render(&Game::Render, this, std::ref(renderer), target_frame_duration, std::ref(running));

  update.join();
  render.join();
}

void Game::Render(Renderer &renderer, std::size_t target_frame_duration, bool &running)
{
    /*
     * Render update the visuals of the game, implementing a timer in order to update the visual at
     * approximately 60 fps
     *
     */

    // Initialize clock element
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    // Init frame count
    int frame_count = 0;
    // Init lock on mutuex for memory access management
    std::unique_lock<std::mutex> space_lock(_space_object_mutex, std::defer_lock);
    std::unique_lock<std::mutex> running_lock(_running_mutex);
    while (running)
    {
        running_lock.unlock();
        frame_start = SDL_GetTicks();
        space_lock.lock();
        // Update visuals on the window
        renderer.Render(_spaceship, _missiles, _mouse, _asteroid);
        space_lock.unlock();
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
        running_lock.lock();
    }
}

void Game::Update(Controller &controller, bool &running) {
    /*
     * Function thread responsible for updating the state of each object following their physics
     * And the user input
     */
    using namespace std::chrono_literals;
    Uint32 end_update;
    Uint32 elapsed_time;
    Uint32 start_update = SDL_GetTicks();
    std::unique_lock<std::mutex> space_lock(_space_object_mutex, std::defer_lock);
    std::unique_lock<std::mutex> running_lock(_running_mutex);
    while(running)
    {
        running_lock.unlock();
        // reducing work load on the update thread in order to avoid overload
        std::this_thread::sleep_for(5ms);
        space_lock.lock();
        // Check for spaceship orientation and add a new missile on mouse click
        controller.HandleInput(running, _spaceship, _missiles, _mouse);
        space_lock.unlock();
        // Update moving element position
        end_update = SDL_GetTicks();
        // compute the time between each while loop in order to update the state of the asteroid and missile
        elapsed_time = end_update - start_update;
        start_update = end_update;
        space_lock.lock();
        // Iterate on the _missiles vector to update the missiles status
        for(Missile &m: _missiles)
        {
            m.update(screen_width, screen_width, elapsed_time);
        }
        // In case the missile gets out of bounds remove it
        _missiles.erase(
                std::remove_if(_missiles.begin(), _missiles.end(), [](const Missile &m){return m.out_of_bounds;}),
                _missiles.end()
        );
        // update asteroid state
        _asteroid.update(screen_width, screen_height, elapsed_time);
        // In case asteroid gets out of bounds respawn it !!! NOTE: should not happen
        if (_asteroid.out_of_bounds)
        {
            _asteroid.spawn();
        }
        running_lock.lock();
        // check for collisions between the spaceship and the asteroid
        // and between a missile and the asteroid
        collisionCheck(running);
        space_lock.unlock();
    }
}

void Game::collisionCheck(bool &running)
{
    /*
     * Check the collision between all the object on the window except for the mouse pointer
     * If a collision occurs between the spaceship and the asteroid the game end
     * If a collision occurs between a missile and the asteroid the score is incremented
     * and the asteroid is set to a new place.
     */
    // collision between the spaceship and asteroid
    if (collision(_spaceship, _asteroid))
    {
        running = false;
    }
    // collision between missile and asteroid
    for (auto &m: _missiles)
    {
        if (collision(m, _asteroid))
        {
            score += 1;
            // Place the asteroid on a new location and increase the speed
            _asteroid.incrementSpeed(10.0);
            _asteroid.spawn();
        }
    }

}

// Valid for all kind of SpaceObject
template<typename T1, typename T2>
bool Game::collision(T1 a, T2 b)
{
    // get necessary data for collision check between two object
    Coordinate pos_a = a.getCoordinatePos();
    Coordinate center_a = a.getImageCenter();
    Coordinate pos_b = b.getCoordinatePos();
    Coordinate center_b = b.getImageCenter();
    return  (
            std::max(pos_a.x, pos_b.x) < std::min(pos_a.x + (center_a.x * 2), pos_b.x + (center_b.x * 2)) &&
            std::max(pos_a.y, pos_b.y) < std::min(pos_a.y + (center_a.y * 2), pos_b.y + (center_b.y * 2))
    );
}

int Game::GetScore() const { return score; }