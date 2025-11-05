#include "../header_files/counting_angles.h"

static calculated_angles *rays_angles = NULL;
static calculated_angles *person_angles = NULL;

void counting_angles() {
	double angles = 0;
	int index = 0;

	rays_angles = malloc(RAYS_COUNT * sizeof(calculated_angles));

	if (!rays_angles) {
	    fprintf(stderr, "Memory allocation failed for rays_angles\n");
	    exit(EXIT_FAILURE);
	}
	
    person_angles = malloc(NUM_PERSON_ANGLES * sizeof(calculated_angles));

    if (!person_angles) {
        fprintf(stderr, "Memory allocation failed for person_angles\n");
        exit(EXIT_FAILURE);
    }

	for (int i = 0; i < RAYS_COUNT; i++) {
		angles = FOV / 2 - i * FOV / (RAYS_COUNT - 1);
	
		rays_angles[i].c_cos = cos(angles);
		rays_angles[i].c_sin = sin(angles);
	}

	for (double i = 0; i < (M_PI * 2); i += ROTATION_STEP) {
		person_angles[index].c_cos = cos(i);
		person_angles[index].c_sin = sin(i);

		index++;
	}

}

double fast_cos(int index, double angle) {
	return  index != NON ? rays_angles[index].c_cos : person_angles[(int) (angle / ROTATION_STEP) % NUM_PERSON_ANGLES].c_cos;
}

double fast_sin(int index, double angle) {
	return  index != NON ? rays_angles[index].c_sin : person_angles[(int) (angle / ROTATION_STEP) % NUM_PERSON_ANGLES].c_sin;
}

void free_arrays() {
	free(rays_angles);
	free(person_angles);

	rays_angles = NULL;
	person_angles = NULL;
}
