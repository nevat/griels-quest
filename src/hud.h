/* hud.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>

# include "array.h"

void show_hud (struct hero griel, SDL_Surface *fonts, SDL_Surface *window, SDL_Surface *blocks, int round);