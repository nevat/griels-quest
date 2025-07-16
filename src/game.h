/* game.h */

#ifndef GAME_H
#define GAME_H

#include "common.h"

#include "array.h"

void game (SDL_Window *screen, uint8_t *state, uint8_t *level);
void show_tiles (struct hero *griel, uint8_t *animationtime, uint8_t map[][11][16], SDL_Texture *blocks, uint8_t round, uint8_t counter, Mix_Chunk *key);
void check_obstacles (struct hero *griel, uint8_t round, uint8_t map[][11][16], Mix_Chunk *kill, uint8_t *grieltouch);
void controls (struct hero *griel, uint8_t *fullscreench);
void loaddata (uint8_t map[][11][16]);
void extralife (struct hero *griel, uint8_t *uplife);
void set_hero_init (struct hero *griel, uint8_t round);
void load_music(Mix_Music *bsogame, int round);
void show_hud (struct hero griel, SDL_Texture *fonts, SDL_Texture *blocks, uint8_t round);
void show_hero (struct hero *griel, uint8_t counter, SDL_Texture *blocks, uint8_t *round, uint8_t *step, uint16_t *waittime, uint8_t *soundblock, Mix_Chunk *giveup);
extern SDL_Renderer *renderer;

#endif
