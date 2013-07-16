/* game.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_rotozoom.h>
# include <SDL_mixer.h>

# include "array.h"

void game (SDL_Surface *screen, uint *state, uint *level);
void show_tiles (struct hero *griel, int *animationtime, int map[][11][16], SDL_Surface *window, SDL_Surface *blocks, int round, int counter, Mix_Chunk *key);
void check_obstacles (struct hero *griel, int round, int map[][11][16], Mix_Chunk *kill, uint *grieltouch);
void controls (struct hero *griel, uint *fullscreench);

