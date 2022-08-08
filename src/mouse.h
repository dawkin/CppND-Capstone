//
// Created by oma on 06.08.22.
//

#ifndef SDL2TEST_MOUSE_H
#define SDL2TEST_MOUSE_H

#include <string>
#include "SDL.h"
#include "spaceObject.h"

class Mouse: public SpaceObject{
public:
    Mouse();
    void update(int screen_w, int screen_h, Uint32 elapsed_time) override;
private:

};


#endif //SDL2TEST_MOUSE_H
