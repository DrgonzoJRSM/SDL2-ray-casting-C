#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include "config.h"
#include "includes.h"
#include "drawing_data.h"

#ifdef USE_TEXTURES
    #include <SDL2/SDL_image.h>
#endif

#define GET_R_FROM_COLOR(color)		    (((color) >> 16) & 0xFF)
#define GET_G_FROM_COLOR(color)		    (((color) >> 8) & 0xFF)
#define GET_B_FROM_COLOR(color)		    ((color) & 0xFF)

extern SDL_Window* window;
extern SDL_Renderer* render;
extern SDL_Texture* texture;

#ifdef USE_TEXTURES
    extern const char* file_location;
#endif

void sdl_init(char* win_name);

#ifdef USE_TEXTURES
    void img_load(void);
#endif

void sdl_quit(void);

void drawing_column(drawing_data* data, int x_coord);

#endif