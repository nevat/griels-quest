/* ending.c */

# include "ending.h"

void ending (SDL_Surface *screen, uint *state) {

	SDL_Surface *blackbox = NULL;
	SDL_Surface *ending1 = NULL;
	SDL_Surface *ending2 = NULL;
	SDL_Surface *ending3 = NULL;
	SDL_Surface *ending4 = NULL;
	SDL_Surface *temp = NULL;

	Mix_Music *bso;
	Mix_Chunk *argh;

	uint waittime = 0;
	uint step = 0;
	uint fadecounter = 255;
	uint counter = 0;
	int framerate = 0;

	/* Loading files */
	temp = IMG_Load("/usr/share/griels/png/blackbox2.png");
	blackbox = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("/usr/share/griels/png/ending1.png");
	ending1 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("/usr/share/griels/png/ending2.png");
	ending2 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("/usr/share/griels/png/ending3.png");
	ending3 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("/usr/share/griels/png/theend.png");
	ending4 = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	argh = Mix_LoadWAV("/usr/share/griels/fx/fx_uaaah.ogg");
	bso = Mix_LoadMUS("/usr/share/griels/music/ending.ogg");

	SDL_Rect srcending = {0,0,512,448};
	SDL_Rect destending = {0,0,512,448};

	while (*state == 3) {
		framerate = control_frames(1,0);
		switch (step) {
			case 0: /* ending 1 */
							SDL_BlitSurface(ending1,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcending,screen,&destending);
							counter ++;
							if (counter == 30)
								Mix_PlayMusic(bso,0);
							if (counter < 85)
								fadecounter-=3;
							if ((counter > 984) && (counter < 1069))
								fadecounter+=3;
							if (counter == 1069) {
								step = 1;
								fadecounter = 255;
							}
							break;
			case 1: /* ending 2 */
							SDL_BlitSurface(ending2,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcending,screen,&destending);
							counter ++;
							if (counter == 1070) /* Demon dying */
								Mix_PlayChannel(0,argh,0);
							if ((counter > 1069) && (counter < 1153))
								fadecounter-=3;
							if ((counter > 2053) && (counter < 2137))
								fadecounter+=3;
							if (counter == 2137) {
								step = 2;
								fadecounter = 255;
							}
							break;
			case 2: /* ending 3 */
							SDL_BlitSurface(ending3,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcending,screen,&destending);
							counter ++;
							if ((counter > 2137) && (counter < 2221))
								fadecounter-=3;
							if ((counter > 3121) && (counter < 3205))
								fadecounter+=3;
							if (counter == 3205) {
								step = 3;
								fadecounter = 255;
							}
							break;
			case 3: /* theend */
							SDL_BlitSurface(ending4,&srcending,screen,&destending);
							/* Transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcending,screen,&destending);
							counter ++;
							if ((counter > 3205) && (counter < 3289))
								fadecounter-=3;
							if (counter == 4189)
								*state = 0;
							break;
		}
		SDL_Flip(screen);
		control_frames(2,framerate);
		SDL_FreeSurface(screen);

	}

	SDL_FreeSurface(ending1);
	SDL_FreeSurface(ending2);
	SDL_FreeSurface(ending3);
	SDL_FreeSurface(ending4);
	SDL_FreeSurface(blackbox);
	Mix_FreeChunk(argh);
	Mix_FreeMusic(bso);

}