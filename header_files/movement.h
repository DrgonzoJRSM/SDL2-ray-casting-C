#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL2/SDL.h>

#include <math.h>

#include "includes.h"
#include "raycasting.h"

void person_movement(person* pr, SDL_KeyCode key);

#endif