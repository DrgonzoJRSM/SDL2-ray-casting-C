#include "graphics.h"

extern SDL_Window* window = NULL;
extern SDL_Renderer* render = NULL;
extern SDL_Texture* texture = NULL;

// extern const char* file_location = "image/1.bmp";

// extern int rect_width = 0;
// extern int rect_height = 0;

void sdl_init(char* win_name) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL init failed!\n%s\n", SDL_GetError());      

        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        win_name, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        fprintf(stderr, "Window init failed!\n%s\n", SDL_GetError());

        exit(EXIT_FAILURE);
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (render == NULL) {
        fprintf(stderr, "Render init failed!\n%s\n", SDL_GetError());

        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTexture(
        render, 
        SDL_PIXELFORMAT_RGB888, 
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    if (texture == NULL) {
        fprintf(stderr, "Texture init failed!\n%s\n", SDL_GetError());

        exit(EXIT_FAILURE);   
    }

}

// void bmp_load(const char* file_name) {
//     SDL_Surface* picture = SDL_LoadBMP(file_name);

//     if (picture == NULL) {
//         fprintf(stderr, "file.pmp load failed!\n%s\n", SDL_GetError());

//         exit(EXIT_FAILURE);
//     }

//     texture = SDL_CreateTextureFromSurface(render, picture);

//     if (texture == NULL) {
//         fprintf(stderr, "Texture creating failed!\n%s\n", SDL_GetError());

//         exit(EXIT_FAILURE);
//     }

//     rect_width = picture->w;
//     rect_height = picture->h;

//     SDL_FreeSurface(picture);
//     picture = NULL;

// }

void sdl_quit() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(render);
    render = NULL;

    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_Quit();
}

// static uint32_t color_selection(drawing_data* data, int y_coord, bool* vertical_edge_flag) {

// 	if (y_coord < data->ceiling_h) {
// 		return CEIL_COLOR;

// 	} else if ((y_coord >= data->ceiling_h) && (y_coord <= data->floor_h)) {
		
// 		if (data->edge_flag) {
// 			return EDGE_COLOR;
		
// 		} else if (!data->edge_flag && ((y_coord == data->ceiling_h) || (y_coord == data->floor_h))) {
// 			*vertical_edge_flag = true;
		
// 			return EDGE_COLOR;
		
// 		} else {
// 			return WALL_COLOR;
// 		}
		
// 	} else if (y_coord > data->floor_h) {
// 		return FLOOR_COLOR;
	
// 	}

// 	return VOID_COLOR;
// }

static void changing_color(float distance_to_wall, uint8_t* r, uint8_t* g, uint8_t* b) {
	float factor = 0.85f - (distance_to_wall / DEPTH);

	if (factor < 0.1f) {
		factor = 0.1f;
	}

	*r = (uint8_t) (*r * factor);
	*g = (uint8_t) (*g * factor);
	*b = (uint8_t) (*b * factor);
}

static void vertical_edge_drawing(SDL_Rect* rect, float distance_to_wall) {
	uint8_t v_r = GET_R_FROM_COLOR(EDGE_COLOR);
	uint8_t v_g = GET_G_FROM_COLOR(EDGE_COLOR);
	uint8_t v_b = GET_B_FROM_COLOR(EDGE_COLOR);	

	changing_color(distance_to_wall, &v_r, &v_g, &v_b);

	SDL_SetRenderDrawColor(render, v_r, v_g, v_b, 0xff);

	for (int i = 0; i < 4; i++) {
		SDL_RenderDrawPoint(render, rect->x, rect->y + i);
		SDL_RenderDrawPoint(render, rect->x, rect->y + rect->h - i);
	}

}

static void rect_drawing(SDL_Rect* rect, uint32_t color, bool edge_flag, float distance_to_wall) {
	bool vertical_edge_flag = false;

	if (edge_flag && (color == WALL_COLOR)) {
		color = EDGE_COLOR;
	} else if (!edge_flag && (color == WALL_COLOR)) {
		vertical_edge_flag = true;
	}

	uint8_t r = GET_R_FROM_COLOR(color);
	uint8_t g = GET_G_FROM_COLOR(color);
	uint8_t b = GET_B_FROM_COLOR(color);

	if (color == WALL_COLOR || color == EDGE_COLOR) {
		changing_color(distance_to_wall, &r, &g, &b);
	}

	SDL_SetRenderDrawColor(render, r, g, b, 0xff);

	SDL_RenderFillRect(render, rect);

	if (vertical_edge_flag) {
		vertical_edge_drawing(rect, distance_to_wall);
	}

}

void drawing_column(drawing_data* data, int x_coord) {
	
	SDL_Rect ceil_rect = {
		.h = data->ceiling_h,
		.w = 1,
		.x = x_coord,
		.y = 0
	};

	SDL_Rect wall_rect = {
		.h = data->floor_h - data->ceiling_h,
		.w = 1,
		.x = x_coord,
		.y = data->ceiling_h
	};

	SDL_Rect floor_rect = {
		.h = SCREEN_HEIGHT - data->floor_h,
		.w = 1,
		.x = x_coord,
		.y = data->floor_h
	};

	rect_drawing(&ceil_rect, CEIL_COLOR, data->edge_flag, data->distance_to_wall);

	rect_drawing(&wall_rect, WALL_COLOR, data->edge_flag, data->distance_to_wall);

	rect_drawing(&floor_rect, FLOOR_COLOR, data->edge_flag, data->distance_to_wall);

	// OLD VERSION
	// for (int y_coord = 0; y_coord < SCREEN_HEIGHT; y_coord++) {
	// 	color = color_selection(data, y_coord, &vertical_edge_flag);

	// 	uint8_t r = GET_R_FROM_COLOR(color);
	// 	uint8_t g = GET_G_FROM_COLOR(color);
	// 	uint8_t b = GET_B_FROM_COLOR(color);

	// 	if ((color == WALL_COLOR) || (color == EDGE_COLOR)) {
	// 		changing_color(data->distance_to_wall, &r, &g, &b);
	// 	}

	// 	SDL_SetRenderDrawColor(render, r, g, b, 0xff);

	// 	SDL_RenderDrawPoint(render, x_coord, y_coord);

	// 	if (vertical_edge_flag) {
	// 		SDL_RenderDrawPoint(render, x_coord, y_coord - 1);
	// 		SDL_RenderDrawPoint(render, x_coord, y_coord - 2);

	// 		vertical_edge_flag = false;
	// 	}
			
	// }
	
}
