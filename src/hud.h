/* hud.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>

# include "array.h"

void show_hud (struct hero griel, SDL_Texture *fonts, SDL_Texture *blocks, uint8_t round);
extern SDL_Renderer *renderer;
