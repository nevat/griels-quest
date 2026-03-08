/* hero.h */

#ifndef HERO_H
#define HERO_H

#include "common.h"

void set_hero_init (hero_s *griel, uint8_t round);
void extralife (hero_s *griel, uint8_t *uplife);
void show_hero (hero_s *griel, uint8_t counter, SDL_Texture *blocks, uint8_t *round, uint8_t *step, uint16_t *waittime, uint8_t *soundblock, Mix_Chunk *giveup);

#endif
