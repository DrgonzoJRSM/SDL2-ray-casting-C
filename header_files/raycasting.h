#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>

#include "config.h"
#include "includes.h"
#include "map.h"
#include "counting_angles.h"
#include "graphics.h"
#include "drawing_data.h"

typedef struct {
	double x_coord;
	double y_coord;
	double angle;
} person;

typedef struct {
	double module;
	double cosine;
} edge_data;

void ray_casting(person* pr);

#endif
