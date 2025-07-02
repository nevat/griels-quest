/* game.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>

# include "array.h"

void game (SDL_Surface *screen, uint8_t *state, uint8_t *level);
void show_tiles (struct hero *griel, uint8_t *animationtime, uint8_t map[][11][16], SDL_Texture *blocks, uint8_t round, uint8_t counter, Mix_Chunk *key);
void check_obstacles (struct hero *griel, uint8_t round, uint8_t map[][11][16], Mix_Chunk *kill, uint8_t *grieltouch);
void controls (struct hero *griel, uint8_t *fullscreench);
