/* hero.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>

# include "array.h"

void set_hero_init (struct hero *griel, uint8_t round);
void extralife (struct hero *griel, uint8_t *uplife);
void show_hero (struct hero *griel, uint8_t counter, SDL_Texture *blocks, uint8_t *round, uint8_t *step, uint16_t *waittime, uint8_t *soundblock, Mix_Chunk *giveup);
extern SDL_Renderer *renderer;
