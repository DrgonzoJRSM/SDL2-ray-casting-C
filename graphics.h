#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include "includes.h"
#include "raycasting.h"
#include "drawing_data.h"

#define SCREEN_WIDTH                640
#define SCREEN_HEIGHT               320

#define RAYS_CONT                   SCREEN_WIDTH

#define CEIL_COLOR					0x918a74
#define WALL_COLOR					0xfab802	
#define EDGE_COLOR					0xf2da96
#define FLOOR_COLOR					0x63593b

#define GET_R_FROM_COLOR(color)		(((color) >> 16) & 0xFF)
#define GET_G_FROM_COLOR(color)		(((color) >> 8) & 0xFF)
#define GET_B_FROM_COLOR(color)		((color) & 0xFF)

extern SDL_Window* window;
extern SDL_Renderer* render;
extern SDL_Texture* texture;

// extern const char* file_location;

// extern int rect_width;   
// extern int rect_height;

void sdl_init(char* win_name);

// void bmp_load(const char* file_name);

void sdl_quit(void);

void drawing_column(drawing_data* data, int x_coord);

#endif