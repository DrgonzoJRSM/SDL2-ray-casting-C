#include <SDL2/SDL.h>

#include "header_files/config.h"
#include "header_files/includes.h"
#include "header_files/raycasting.h"
#include "header_files/counting_angles.h"
#include "header_files/graphics.h"
#include "header_files/movement.h"

int main() {
    srand(time(NULL));

    counting_angles();

	person pr = {
		.x_coord = 1.5,
		.y_coord = 1.5,
		.angle = 0
	};

    sdl_init("first");

    #ifdef USE_TEXTURES
        img_load();
    #endif
    
    bool run = true;
    
    SDL_Event event;

    while (run) {
        while (SDL_PollEvent(&event) != 0) {

            switch (event.type) {
                case SDL_QUIT:
                    run = false;
                    
                    break;
                
                case SDL_KEYDOWN:
                    person_movement(&pr, event.key.keysym.sym);

                    break;

                default:
                    break;

            }

        }

        SDL_RenderClear(render);

        ray_casting(&pr);

        SDL_RenderCopy(render, texture, NULL, NULL);

        SDL_RenderPresent(render);

        SDL_Delay(DELAY_MS);
    }

    free_arrays();
    
    sdl_quit();

    return 0;
}






