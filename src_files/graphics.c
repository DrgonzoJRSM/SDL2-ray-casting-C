#include "../header_files/graphics.h"

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;

#ifdef USE_TEXTURES
	SDL_Texture* image_texture = NULL;

	int image_height = 0;
	int image_width = 0;
#endif

void sdl_init(char* win_name) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL init failed!\n%s\n", SDL_GetError());      

        exit(EXIT_FAILURE);
    }

	#ifdef USE_TEXTURES
		int flag =  IMG_INIT_JPG;

		if (!(IMG_Init(flag) & flag)) {
			fprintf(stderr, "SDL_Image init failed!\n%s\n", IMG_GetError());      

			exit(EXIT_FAILURE);
		}
	#endif

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

#ifdef USE_TEXTURES
	void img_load() {
		SDL_Surface* image = IMG_Load(TEXTURE_FILE);

		if (image == NULL) {
			fprintf(stderr, "file.png load failed!\n%s\n", IMG_GetError());

			exit(EXIT_FAILURE);
		}

		image_height = image->h;
		image_width = image->w;

		image_texture = SDL_CreateTextureFromSurface(render, image);

		if (image_texture == NULL) {
			fprintf(stderr, "Texture creating failed!\n%s\n", SDL_GetError());

			exit(EXIT_FAILURE);
		}

		SDL_FreeSurface(image);
		image = NULL;
	}
#endif

void sdl_quit() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(render);
    render = NULL;

    SDL_DestroyTexture(texture);
    texture = NULL;

	SDL_Quit();

	#ifdef USE_TEXTURES 
		SDL_DestroyTexture(image_texture);
		image_texture = NULL;
		
		
		IMG_Quit();
	#endif
}

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

	rect_drawing(&ceil_rect, CEIL_COLOR, data->edge_flag, data->distance_to_wall);

	SDL_Rect wall_rect = {
		.h = data->floor_h - data->ceiling_h,
		.w = 1,
		.x = x_coord,
		.y = data->ceiling_h
	};

	#ifdef USE_TEXTURES
		SDL_Rect src_rect = {
			.h = image_height,
			.w = 1,
			.x = (int) (data->image_x_coord * image_width),
			.y = 0
		};

		SDL_RenderCopy(render, image_texture, &src_rect, &wall_rect);
	#else
		rect_drawing(&wall_rect, WALL_COLOR, data->edge_flag, data->distance_to_wall);
	#endif
		
	SDL_Rect floor_rect = {
		.h = SCREEN_HEIGHT - data->floor_h,
		.w = 1,
		.x = x_coord,
		.y = data->floor_h
	};

	rect_drawing(&floor_rect, FLOOR_COLOR, data->edge_flag, data->distance_to_wall);
}
