/* intro.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_rotozoom.h>
# include <SDL_mixer.h>

void game_intro (SDL_Surface *screen, uint *state, uint *level);
int passwvalidate (uint passint[]);