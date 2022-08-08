//
// Created by oma on 05.08.22.
//

#ifndef SDL2TEST_ASTEROID_H
#define SDL2TEST_ASTEROID_H

#include "spaceObject.h"


class Asteroid : public SpaceObject{
public:
    Asteroid();
    void update(int screen_w, int screen_h, Uint32 elapsed_time) override;
    void spawn();
    bool out_of_bounds = false;
private:
    void outOfBounds(int screen_w, int screen_h, float pos_x, float pos_y);
    Speed _speed;
};


#endif //SDL2TEST_ASTEROID_H
