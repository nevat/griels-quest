
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// constants

#define SCREEN_W 256
#define SCREEN_H 224
#define VERSION "1.0.1"

// custom types

typedef enum {
	GS_INTRO,
	GS_HISTORY,
	GS_GAME,
	GS_ENDING,
	GS_EXIT
} GameScene;

typedef enum {
	CR_DECISION,
	CR_POW,
	CR_DEATH,
	CR_GRAIL
} ControllerRumble;

typedef struct {
	int score;
	uint lifes;
	uint object;
	uint key;
	uint x;
	uint y;
	uint positionx;
	uint positiony;
	uint direction;
	uint locked;
	uint movement;
	uint endanimation;
	uint deathanimation;
	uint deathturns;
	uint killed;
	uint grial;
} hero_s;

typedef struct {
	SDL_Renderer *renderer;

	GameScene scene;
	uint8_t level;
} state_s;

// globals
extern state_s g_state;

#endif // COMMON_H
