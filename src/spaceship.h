//
// Created by oma on 05.08.22.
//

#ifndef SDL2TEST_SPACESHIP_H
#define SDL2TEST_SPACESHIP_H

#include <string>
#include "SDL.h"
#include "spaceObject.h"

class Spaceship : public SpaceObject {
public:
    Spaceship();
    void update(int screen_w, int screen_h, Uint32 elapsed_time) override;
    void setAngle(int x, int y);
    Coordinate getShootingPoint();
private:

};

#endif //SDL2TEST_SPACESHIP_H
