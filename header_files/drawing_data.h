#ifndef DRAWING_DATA_H
#define DRAWING_DATA_H

#include "config.h"

typedef struct {
	bool edge_flag;
	double distance_to_wall;

	#ifdef USE_TEXTURES
		double image_x_coord;
	#endif
	
	int ceiling_h;
	int floor_h;
} drawing_data;

#endif