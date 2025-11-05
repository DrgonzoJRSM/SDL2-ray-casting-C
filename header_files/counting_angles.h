#ifndef COUNTING_ANGLES_H
#define COUNTING_ANGLES_H

#include <math.h>

#include "config.h"
#include "includes.h"
#include "raycasting.h"

#define NUM_PERSON_ANGLES	((int) (M_PI * 20 / ROTATION_STEP))
    
#define NON					-1

typedef struct {
	double c_sin;
	double c_cos;
} calculated_angles;

void counting_angles(void);

double fast_cos(int index, double angle);

double fast_sin(int index, double angle);

double get_angle(int x_coord);

void free_arrays(void);

#endif
