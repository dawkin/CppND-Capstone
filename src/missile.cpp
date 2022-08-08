//
// Created by oma on 06.08.22.
//

#include "missile.h"
#include "SDL.h"
#include <cmath>

#define PI 3.14159265358979323846

Missile::Missile(): SpaceObject("../missile.bmp") {}

void Missile::update(int screen_w, int screen_h, Uint32 elapsed_time) {
    Coordinate pos = SpaceObject::getCoordinatePos();
    pos.x += _speed.v * cos((_speed.theta - 90) * PI / 180.0) * (elapsed_time / 1000.0);
    pos.y += _speed.v * sin((_speed.theta - 90) * PI / 180.0) * (elapsed_time / 1000.0);
    SpaceObject::setPos(pos);
    outOfBounds(screen_w, screen_h, pos.x, pos.y);
}

void Missile::outOfBounds(int screen_w, int screen_h, float pos_x, float pos_y)
{
    out_of_bounds = (pos_x < 0.0 || pos_x > (float) screen_w) || (pos_y < 0.0 || pos_y > (float) screen_h);
}

void Missile::setSpeed(float v, float theta)
{
    _speed.v = v;
    _speed.theta = theta;
}
