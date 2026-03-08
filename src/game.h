/* game.h */

#ifndef GAME_H
#define GAME_H

#include "common.h"

void game ();
void show_tiles (hero_s *griel, uint8_t *animationtime, uint8_t map[][11][16], SDL_Texture *blocks, uint8_t round, uint8_t counter, Mix_Chunk *key);
void check_obstacles (hero_s *griel, uint8_t round, uint8_t map[][11][16], Mix_Chunk *kill, uint8_t *grieltouch);
void loaddata (uint8_t map[][11][16]);
void extralife (hero_s *griel, uint8_t *uplife);
void set_hero_init (hero_s *griel, uint8_t round);
void load_music(Mix_Music *bsogame, int round);
void show_hud (hero_s griel, SDL_Texture *fonts, SDL_Texture *blocks, uint8_t round);
void show_hero (hero_s *griel, uint8_t counter, SDL_Texture *blocks, uint8_t *round, uint8_t *step, uint16_t *waittime, uint8_t *soundblock, Mix_Chunk *giveup);

#endif
