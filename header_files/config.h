#ifndef CONFIG_H
#define CONFIG_H

#include <math.h>

// #define USE_TEXTURES

#define SCREEN_WIDTH                    640
#define SCREEN_HEIGHT                   320

#define WALL_COLOR                      0xfab802
#define CEIL_COLOR					    0x918a74
#define EDGE_COLOR					    0xf2da96
#define FLOOR_COLOR					    0x63593b

#define RAYS_CONT                       SCREEN_WIDTH

#define FOV 						    M_PI / 3 	// Угол обзора игрока

#define MOVEMENT_STEP				    0.1 		
#define ROTATION_STEP				    0.025 		// Угол поворота взгляда игрока
#define EDGE_ANGLE_FACTOR			    0.01 		// Коэффициент для рассчета ребер
#define STEP_PRECISION 				    0.01		// Шаг для поиска расстояния до стены
			
#define DEPTH						    10 			// Дальность прорисовки

#ifdef USE_TEXTURES
    #define TEXTURE_FILE                "image/2.png"
#endif

#define DELAY_MS                        16

#endif