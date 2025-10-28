#include <SDL2/SDL.h>

#include "includes.h"

#include "counting_angles.h"
#include "graphics.h"
#include "movement.h"
#include "raycasting.h"



int main() {
    srand(time(NULL));

    counting_angles();

	person pr = {
		.x_coord = 1.5,
		.y_coord = 1.5,
		.angle = 0
	};

    sdl_init("first");    

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

        SDL_Delay(16);
    }

    free_arrays();
    
    sdl_quit();

    return 0;
}






