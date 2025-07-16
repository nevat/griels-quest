/* main.h */

#ifndef MAIN_H
#define MAIN_H

#include "common.h"

void history (SDL_Window *screen, uint8_t *state);
void game (SDL_Window *screen, uint8_t *state, uint8_t *level);
void game_intro (SDL_Window *screen, uint8_t *state, uint8_t *level);
void ending (SDL_Window *screen, uint8_t *state);

#endif
