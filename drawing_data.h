#ifndef DRAWING_DATA_H
#define DRAWING_DATA_H

typedef struct {
	double distance_to_wall;
	int ceiling_h;
	int floor_h; 
	bool edge_flag;
} drawing_data;

#endif