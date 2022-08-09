//
// Created by oma on 05.08.22.
//

#include "SDL.h"
#include "asteroid.h"
#include <cmath>
#include <random>
#include <chrono>

#define PI 3.14159265358979323846

Asteroid::Asteroid() : SpaceObject("../asteroid.bmp"), _speed({100.0, 0.0})
{
    // define a random position for the asteroid
    spawn();
}

void Asteroid::spawn()
{
    // take a random angle for asteroid
    // generate a seed for random based on epoch
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> dist(0.0 , 359.9);
    _speed.theta = dist(generator);
    int spawn_pos_x = (int) (320.0 + 300.0 * cos(_speed.theta * PI / 180.0));
    int spawn_pos_y = (int) (320.0 + 300.0 * sin(_speed.theta * PI / 180.0));
    SpaceObject::definePosition(spawn_pos_x, spawn_pos_y);
}

void Asteroid::update(int screen_w, int screen_h, Uint32 elapsed_time) {
    // Update asteroid postion based elapsed time and internal speed vector
    Coordinate pos = SpaceObject::getCoordinatePos();
    pos.x -= _speed.v * cos((_speed.theta) * PI / 180.0) * (elapsed_time / 1000.0);
    pos.y -= _speed.v * sin((_speed.theta) * PI / 180.0) * (elapsed_time / 1000.0);
    SpaceObject::setPos(pos);
    outOfBounds(screen_w, screen_h, pos.x, pos.y);
}

void Asteroid::outOfBounds(int screen_w, int screen_h, float pos_x, float pos_y)
{
    // Check if asteroid went out of bounds
    out_of_bounds = (pos_x < 0.0 || pos_x > (float) screen_w) || (pos_y < 0.0 || pos_y > (float) screen_h);
}

void Asteroid::incrementSpeed(float increment)
{
    _speed.v += increment;
}