/* Griel's Quest for the Sangraal */
/* Started on 17/04/2013 */
/* Under GPL v3 license */

# include "main.h"

void main() {

	SDL_Surface *screen = NULL;
	uint state = 0;
	uint level = 0;

	/* starting SDL */
	initsdl();
	screen = SDL_SetVideoMode(512,448,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	/* Loading part of the game */
	while (state < 4) {
		switch (state) {
			case 0: game_intro (screen, &state, &level);
							break;
			case 1: history (screen, &state);
							break;
			case 2: game (screen, &state, &level);
							break;
			case 3: ending (screen,&state);
							break;
		}
	}

}

void initsdl() {

	/* Center the window */
	putenv("SDL_VIDEO_CENTERED=1");

	/* Init SDLVideo */
		if (SDL_Init(SDL_INIT_VIDEO)<0) {
			printf("Error starting SDL: %s\n",SDL_GetError());
			exit(1);
		}
		atexit(SDL_Quit);
	/* Init SDLTTF */
	  if (TTF_Init() < 0) {
			printf("Error starting SDL_ttf: %s\n",SDL_GetError());
			exit(1);
		}
		atexit(TTF_Quit);

	  if (Mix_OpenAudio (44100, AUDIO_S16, 1, 4096)) {
        printf("No se pudo inicializar SDL_Mixer %s\n",Mix_GetError());
        exit(1);
		}
		Mix_AllocateChannels(3);
		atexit(Mix_CloseAudio);

	/* Name of the window */
		SDL_WM_SetCaption("Griel's Quest for the Sangraal", "Griel's Quest");

	/* Disable cursor */
		SDL_ShowCursor(SDL_DISABLE);

	/* Disable repeat keys */
	  SDL_EnableKeyRepeat(0, 0);

}

int control_frames (int i, int frate) {

	int now = SDL_GetTicks();

	if (i==1)
		return now;

	if (i==2) {
		int diff = now - frate;
		if (diff<16)
			SDL_Delay(16-diff);
		return 0;
	}

}