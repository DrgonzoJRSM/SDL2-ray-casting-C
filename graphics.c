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

static uint32_t color_selection(drawing_data* data, int y_coord, bool* vertical_edge_flag) {

	if (y_coord < data->ceiling_h) {
		return VOID_COLOR;

	} else if ((y_coord >= data->ceiling_h) && (y_coord <= data->floor_h)) {
		
		if (data->edge_flag) {
			return EDGE_COLOR;
		
		} else if (!data->edge_flag && ((y_coord == data->ceiling_h) || (y_coord == data->floor_h))) {
			*vertical_edge_flag = true;
		
			return EDGE_COLOR;
		
		} else {
			return WALL_COLOR;
		}
		
	} else if (y_coord > data->floor_h) {
		return FLOOR_COLOR;
	
	}

	return VOID_COLOR;
}

static void changing_color(float distance_to_wall, uint8_t* r, uint8_t* g, uint8_t* b) {
	float factor = 1.0f - (distance_to_wall / DEPTH);

	if (factor < 0.1f) {
		factor = 0.1f;
	}

	if (factor > 1.0f) {
		factor = 1.0f;
	}

	*r = (uint8_t) (*r * factor);
	*g = (uint8_t) (*g * factor);
	*b = (uint8_t) (*b * factor);
}

void drawing_column(drawing_data* data, int x_coord) {
	uint32_t color = 0;	

	bool vertical_edge_flag = false;
	
	for (int y_coord = 0; y_coord < SCREEN_HEIGHT; y_coord++) {
		color = color_selection(data, y_coord, &vertical_edge_flag);

		uint8_t r = GET_R_FROM_COLOR(color);
		uint8_t g = GET_G_FROM_COLOR(color);
		uint8_t b = GET_B_FROM_COLOR(color);

		if ((color == WALL_COLOR) || (color == EDGE_COLOR)) {
			changing_color(data->distance_to_wall, &r, &g, &b);
		}

		SDL_SetRenderDrawColor(render, r, g, b, 0xff);

		SDL_RenderDrawPoint(render, x_coord, y_coord);

		if (vertical_edge_flag) {
			SDL_RenderDrawPoint(render, x_coord, y_coord - 1);
			SDL_RenderDrawPoint(render, x_coord, y_coord - 2);

			vertical_edge_flag = false;
		}
			
	}
	
}
