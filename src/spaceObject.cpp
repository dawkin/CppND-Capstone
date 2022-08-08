//
// Created by oma on 05.08.22.
//
#include "spaceObject.h"
#include "SDL.h"
#include <string>

SpaceObject::SpaceObject(std::string filename):
    _texture(nullptr), _angle(0.0),
    _position({0.0, 0.0})
{
    // Load Image from bitmap
    _image = SDL_LoadBMP(filename.c_str());
    // Define image center
    _image_center.x = ((float)_image->w) /2;
    _image_center.y = ((float)_image->h) /2;
}


void SpaceObject::setPos(SDL_Rect pos)
{
    _position.x = (float) pos.x;
    _position.y = (float) pos.y;
}

void SpaceObject::setPos(Coordinate pos)
{
    _position.x = pos.x;
    _position.y = pos.y;
}

SDL_Rect SpaceObject::getRectPos()
{
    SDL_Rect position{(int) _position.x, (int) _position.y, 0, 0};
    return position;
}

Coordinate SpaceObject::getCoordinatePos()
{
    return _position;
}

void SpaceObject::definePosition(int w, int h)
{
    // Define the position for spaceship object
    _position.x = (float) w - _image_center.x;
    _position.y = (float) h - _image_center.y;
}

void SpaceObject::loadTexture(SDL_Renderer *renderer)
{
    _texture = SDL_CreateTextureFromSurface(renderer, _image);
}