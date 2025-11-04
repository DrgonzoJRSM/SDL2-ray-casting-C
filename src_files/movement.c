#include "../header_files/movement.h"

void person_movement(person* pr, SDL_KeyCode key) {
	double calc_sin = fast_sin(NON, pr->angle);
	double calc_cos = fast_cos(NON, pr->angle);
	
	double temp_x = pr->x_coord;
	double temp_y = pr->y_coord;

	switch (key) {
		case SDLK_a: 
			pr->angle += ROTATION_STEP;

			break;
		case SDLK_d:
			pr->angle -= ROTATION_STEP;

			break;
		case SDLK_w:
			temp_x += MOVEMENT_STEP * calc_sin;
			temp_y += MOVEMENT_STEP * calc_cos;
		
			break;
		case SDLK_s:
			temp_x -= MOVEMENT_STEP * calc_sin;
			temp_y -= MOVEMENT_STEP * calc_cos;

			break;
		default:
			break;
	}

	pr->x_coord = temp_x;
	pr->y_coord = temp_y;
	pr->angle = fmod(pr->angle, 2 * M_PI);

	if (pr->angle < 0) {
		pr->angle += 2 * M_PI;
	}
	
}