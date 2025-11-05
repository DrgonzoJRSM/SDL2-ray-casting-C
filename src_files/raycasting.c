#include "../header_files/raycasting.h"

// static int compare(const void* a, const void* b) {
// 	const edge_data* edge_a = (const edge_data*) a;
// 	const edge_data* edge_b = (const edge_data*) b;

// 	if (edge_a->module < edge_b->module) {
// 		return -1;
// 	}

// 	if (edge_a->module > edge_b->module) {
// 		return 1;
// 	}

// 	return 0;
// }

static void sort_edges(edge_data* edges, int size) {

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {

            if (edges[j].module > edges[j + 1].module) {
                edge_data temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }

        }
    }

}

static bool counting_edge_flag(person* pr, double test_x, double test_y, double ray_x, double ray_y, double distance_to_wall) {
	edge_data edge_arr[4] = {0};
	bool edge_flag = 0;

	int index = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			double v_x = test_x + i - pr->x_coord; 
			double v_y = test_y + j - pr->y_coord;

			double module = sqrt(v_x * v_x + v_y * v_y);

			edge_arr[index].module = module;
			edge_arr[index].cosine = (ray_x * v_x + ray_y * v_y) / module;

			index++;
		}
	}

	// qsort(edge_arr, 4, sizeof(edge_data), compare);
	sort_edges(edge_arr, 4);

	double edge_angle = EDGE_ANGLE_FACTOR / distance_to_wall;

	edge_flag = (edge_arr[0].cosine > cos(edge_angle)) ||
				(edge_arr[1].cosine > cos(edge_angle)
	);
	
	return edge_flag;	
}

#ifdef USE_TEXTURES
static double search_image_x_coord(person* pr, double ray_x, double ray_y, double distance_to_wall) {
	return 0;
}

#endif


void ray_casting(person* pr) {

	for (int x_coord = 0; x_coord < RAYS_COUNT; x_coord++) {	
		drawing_data data = {0};
		
		double ray_x = fast_sin(NON, pr->angle) * fast_cos(x_coord, NON) + fast_cos(NON, pr->angle) * fast_sin(x_coord, NON);
		double ray_y = fast_cos(NON, pr->angle) * fast_cos(x_coord, NON) - fast_sin(NON, pr->angle) * fast_sin(x_coord, NON);
		
		bool wall_flag = false;

		int test_x = 0;
		int test_y = 0;

		while (!wall_flag) {
			data.distance_to_wall += STEP_PRECISION;

			test_x = (int) (pr->x_coord + ray_x * data.distance_to_wall);
			test_y = (int) (pr->y_coord + ray_y * data.distance_to_wall);

			if (test_x < 0 || test_x >= DEPTH + pr->x_coord || test_y < 0 || test_y >= DEPTH + pr->y_coord) {
				wall_flag = 1;
				data.distance_to_wall = DEPTH;
			} else if (map[test_y][test_x]) {
				wall_flag = true;
				data.distance_to_wall -= STEP_PRECISION;
				data.edge_flag = counting_edge_flag(pr, test_x, test_y, ray_x, ray_y, data.distance_to_wall);
			} 
			
		}
		
		data.distance_to_wall = data.distance_to_wall * fast_cos(x_coord, NON);;
		data.ceiling_h = (int) (SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / data.distance_to_wall);
		data.floor_h = SCREEN_HEIGHT - data.ceiling_h;

		#ifdef USE_TEXTURES
			data.image_x_coord = search_image_x_coord(pr, ray_x, ray_y, data.distance_to_wall);
		#endif

		SDL_SetRenderTarget(render, texture);

		drawing_column(&data, x_coord);

		SDL_SetRenderTarget(render, NULL);
	}

}
