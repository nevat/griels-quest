/* hud.h */

#ifndef HUD_H
#define HUD_H

#include "common.h"
#include "array.h"

void show_hud (struct hero griel, SDL_Texture *fonts, SDL_Texture *blocks, uint8_t round);
extern SDL_Renderer *renderer;

#endif
