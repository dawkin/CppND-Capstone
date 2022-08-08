//
// Created by oma on 06.08.22.
//

#ifndef SDL2TEST_MISSILE_H
#define SDL2TEST_MISSILE_H

#include "spaceObject.h"

class Missile : public SpaceObject {
public:
    Missile();
    void update(int screen_w, int screen_h, Uint32 elapsed_time) override;
    void setSpeed(float v, float theta);
    bool out_of_bounds = false;

private:
    void outOfBounds(int screen_w, int screen_h, float pos_x, float pos_y);
    Speed _speed;
};


#endif //SDL2TEST_MISSILE_H
