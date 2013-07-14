/* ending.c */

# include "ending.h"

void ending (SDL_Surface *screen, uint *state) {

	SDL_Surface *blackbox = NULL;
	SDL_Surface *ending1 = NULL;
	SDL_Surface *ending2 = NULL;
	SDL_Surface *ending3 = NULL;
	SDL_Surface *ending4 = NULL;
	SDL_Surface *temp = NULL;

	uint waittime = 0;
	uint step = 0;
	uint fadecounter = 255;
	uint counter = 0;

	/* Loading files */
	temp = IMG_Load("../png/blackbox2.png");
	blackbox = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/ending1.png");
	ending1 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/ending2.png");
	ending2 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/ending3.png");
	ending3 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/theend.png");
	ending4 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	SDL_Rect srcending = {0,0,512,448};
	SDL_Rect destending = {0,0,512,448};

	while (*state == 4) {
		framerate = control_frames(1,0);
		switch (step) {
			case 0: /* ending 1 */
							SDL_BlitSurface(ending1,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcscreen,screen,&destscreen);
							counter ++;
							if (counter < 85)
								fadecounter-=3;
							if ((counter > 854) && (counter < 941))
								fadecounter+=3;
							if (counter == 940) {
								step = 1;
								fadecounter = 255;
							}
							break;
			case 1: /* ending 1 */
							SDL_BlitSurface(ending1,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcscreen,screen,&destscreen);
							counter ++;
							if ((counter > 940) && (counter < 1026))
								fadecounter-=3;
							if ((counter > 1925) && (counter < 1987))
								fadecounter+=3;
							if (counter == 1987) {
								step = 2;
								fadecounter = 255;
							}
							break;
		}
		control_frames(2,framerate);

	}

}