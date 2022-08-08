//
// Created by oma on 05.08.22.
//

#ifndef SDL2TEST_SPACEOBJECT_H
#define SDL2TEST_SPACEOBJECT_H

#include <string>
#include <memory>
#include "SDL.h"

typedef struct {
    float x;
    float y;
} Coordinate;

typedef  struct {
    float v;
    float theta;
} Speed;

class SpaceObject {
public:
    /* Constructor / Desctructor */
    SpaceObject(std::string filename);

    /* Getter / Setter */
    SDL_Rect getRectPos();
    Coordinate getCoordinatePos();
    void setPos(SDL_Rect pos);
    void setPos(Coordinate pos);
    Coordinate getImageCenter() {return _image_center;};
    SDL_Texture * getTexture() {return _texture;};
    float getAngle() {return _angle;};
    void setAngle(float angle){_angle = angle;};

    /* Public Methods */
    void loadTexture(SDL_Renderer* renderer);
    void definePosition(int w, int h);
    virtual void update(int screen_w, int screen_h, Uint32 elapsed_time) = 0;

private:
    /* Private methods */

    /* Private attributes */
    SDL_Surface * _image;
    Coordinate _image_center;
    SDL_Texture * _texture;
    Coordinate _position;
    float _angle;
};

#endif //SDL2TEST_SPACEOBJECT_H
