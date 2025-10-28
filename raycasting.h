#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>

#include "includes.h"
#include "counting_angles.h"
#include "graphics.h"
#include "map.h"
#include "drawing_data.h"

#define FOV 						M_PI / 3 	// Угол обзора игрока

#define MOVEMENT_STEP				0.1 		
#define ROTATION_STEP				0.02 		// Угол поворота взгляда игрока
#define EDGE_ANGLE_FACTOR			0.01 		// Коэффициент для рассчета ребер
			
#define DEPTH						8 			// Дальность прорисовки

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
