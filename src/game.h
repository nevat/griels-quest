/* game.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_rotozoom.h>
# include <SDL_mixer.h>

# include "array.h"

void game (SDL_Surface *screen, uint *state, uint *level);
void loaddata (int map[][11][16]);
void show_hud (struct hero griel, SDL_Surface *fonts, SDL_Surface *window, SDL_Surface *blocks, int round);
void show_tiles (struct hero *griel, int *animationtime, int map[][11][16], SDL_Surface *window, SDL_Surface *blocks, int round, int counter);
void check_obstacles (struct hero *griel, int round, int map[][11][16]);
void show_hero (struct hero *griel, int counter, SDL_Surface *window, SDL_Surface *blocks, int *round, int *step, uint *waittime);
void controls (struct hero *griel);
void load_music(Mix_Music *bso, int round);
void set_hero_init (struct hero *griel, int round);
void extralife (struct hero *griel, uint *uplife);