/* intro.h */

#ifndef INTRO_H
#define INTRO_H

#include "common.h"

void game_intro (SDL_Window *screen, uint8_t *state, uint8_t *level);
uint8_t passwvalidate (uint8_t passint[]);
extern SDL_Renderer *renderer;

#endif
