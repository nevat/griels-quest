/* main.h */

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_rotozoom.h>
# include <SDL_ttf.h>
# include <SDL_getenv.h>
# include <SDL_mixer.h>

void initsdl();
int control_frames (int i, int frate);
void history (SDL_Surface *screen, uint *state);