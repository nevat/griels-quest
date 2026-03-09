/* loading.h */

#ifndef LOADING_H
#define LOADING_H

#include "common.h"

void loaddata (uint8_t map[][11][16]);
void load_music(Mix_Music *bsogame, int round);
SDL_Texture *loadtexture(const char *file);
Mix_Music *loadmus(const char *file);
Mix_Chunk *loadwav(const char *file);
bool check_data();

#endif
