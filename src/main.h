/* main.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>

void history (SDL_Window *screen, uint8_t *state);
void game (SDL_Window *screen, uint8_t *state, uint8_t *level);
void game_intro (SDL_Window *screen, uint8_t *state, uint8_t *level);
void ending (SDL_Window *screen, uint8_t *state);
