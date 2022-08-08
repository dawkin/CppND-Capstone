//
// Created by oma on 05.08.22.
//

#include "spaceship.h"
#include "SDL.h"
#include <cmath>

#define PI 3.14159265358979323846

Spaceship::Spaceship(): SpaceObject("../spaceship.bmp") {}
void Spaceship::update(int screen_w, int screen_h, Uint32 elapsed_time) {}

void Spaceship::setAngle(int x, int y)
{
    // Set angle for the spaceship based on the spaceship location and the mouse pointer
    SDL_Rect pos = SpaceObject::getRectPos();
    Coordinate image_center = SpaceObject::getImageCenter();
    auto mid_x = (float) (pos.x + image_center.x);
    auto mid_y = (float) (pos.y + image_center.y);
    SpaceObject::setAngle(-90.0 + atan2(mid_y - ((float) y),mid_x - ((float) x)) * (180 / PI));
}

Coordinate Spaceship::getShootingPoint()
{

    SDL_Rect pos = SpaceObject::getRectPos();
    int radius = (int) SpaceObject::getImageCenter().y;
    float angle = SpaceObject::getAngle();
    Coordinate shooting_point;
    shooting_point.x =  (float) ((2 * radius * cos((angle - 90) * PI / 180)) + pos.x + radius);
    shooting_point.y =  (float) ((2 * radius * sin((angle - 90) * PI / 180)) + pos.y + radius);
    return shooting_point;
}

