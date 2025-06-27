/* intro.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>

void game_intro (SDL_Window *screen, uint8_t *state, uint8_t *level);
uint8_t passwvalidate (uint8_t passint[]);
extern SDL_Renderer *renderer;
