#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "spaceship.h"
#include "missile.h"
#include "mouse.h"
#include <vector>

class Controller {
public:
    void HandleInput(bool &running, Spaceship &spaceship, std::vector<Missile> &missiles, Mouse &mouse);

private:

};

#endif