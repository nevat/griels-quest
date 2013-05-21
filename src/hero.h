/* hero.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>

# include "array.h"

void set_hero_init (struct hero *griel, int round);
void extralife (struct hero *griel, uint *uplife);
void show_hero (struct hero *griel, int counter, SDL_Surface *window, SDL_Surface *blocks, int *round, int *step, uint *waittime);
