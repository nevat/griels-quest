/* intro.c */

# include "intro.h"

void game_intro (SDL_Surface *screen, uint *state, uint *level) {

	SDL_Surface *blackbox = NULL;
	SDL_Surface *karoshi = NULL;
	SDL_Surface *window = NULL;
	SDL_Surface *temp = NULL;
	SDL_Surface *doble = NULL;
	SDL_Surface *blocks = NULL;
	SDL_Surface *startscreen = NULL;
	SDL_Surface *startinfo = NULL;
	SDL_Surface *menu = NULL;
	SDL_Surface *arrow = NULL;
	SDL_Surface *passwords = NULL;

	SDL_Event keystroke;

	/* Load files */
	temp = IMG_Load("../png/blackbox.png");
	blackbox = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/karoshi.png");
	karoshi = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/blackbox.png");
	window = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/startscreen.png");
	startscreen = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/startinfo.png");
	startinfo = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/blocks.png");
	blocks = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/menu.png");
	menu = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/fonts.png");
	arrow = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/password.png");
	passwords = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);

	SDL_Rect srcscreen = {0,0,256,224};
	SDL_Rect destscreen = {0,0,256,224};
	SDL_Rect srctext = {0,0,200,20};
	SDL_Rect destext = {28,20,200,20};
	SDL_Rect srcblocks = {0,0,16,16};
	SDL_Rect destblocks = {0,0,16,16};
	SDL_Rect srcarrow = {40,40,8,8};
	SDL_Rect desarrow = {80,88,8,8};
	SDL_Rect srcselector = {0,224,14,14};
	SDL_Rect destselector = {61,101,14,14};

	uint step = 0;
	int framerate = 0;
	uint counter = 0;
	uint fadecounter = 255;
	uint animcounter = 0;
	uint posarrow = 0;
	uint selectorpos = 1;
	uint passint[8] = {0,0,0,0,0,0,0,0};
	uint n = 0;

	/* Loop */
	while (*state == 0) {
		framerate = control_frames(1,0);
		switch (step) {
			case 0: /* Karoshi logo */
							SDL_BlitSurface(karoshi,&srcscreen,window,&destscreen);
							/* Apply transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcscreen,window,&destscreen);
							counter ++;
							while (SDL_PollEvent(&keystroke)) {
								if (keystroke.type == SDL_QUIT)
									exit(0);
								if (keystroke.type == SDL_KEYDOWN) {
									if (keystroke.key.keysym.sym == SDLK_ESCAPE)
										exit(0);
									if (keystroke.key.keysym.sym == SDLK_SPACE) {
										counter = 341;;
										step = 1;
										fadecounter = 255;
									}
								}
							}
							if (counter < 85)
								fadecounter-=3;
							if ((counter > 254) && (counter < 341))
								fadecounter+=3;
							if (counter == 340) {
								step = 1;
								fadecounter = 255;
							}
							break;
			case 1: /* Press start screen */
							SDL_BlitSurface(startscreen,&srcscreen,window,&destscreen);
							/* Apply transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,&srcscreen,window,&destscreen);
							counter ++;
							while (SDL_PollEvent(&keystroke)) {
								if (keystroke.type == SDL_QUIT)
									exit(0);
								if (keystroke.type == SDL_KEYDOWN) {
									if (keystroke.key.keysym.sym == SDLK_ESCAPE)
										exit(0);
									if (keystroke.key.keysym.sym == SDLK_SPACE)
										step = 3;
								}
							}
							if ((counter > 340) && (counter < 426))
								fadecounter-=3;
							if ((counter > 1325) && (counter < 1387))
								fadecounter+=3;
							if (counter == 1387) {
								step = 2;
								fadecounter = 255;
							}
							break;
			case 2: /* Show instructions */
							SDL_BlitSurface(startinfo,&srcscreen,window,&destscreen);
							counter ++;
							while (SDL_PollEvent(&keystroke)) {
								if (keystroke.type == SDL_QUIT)
									exit(0);
								if (keystroke.type == SDL_KEYDOWN) {
									if (keystroke.key.keysym.sym == SDLK_ESCAPE)
										exit(0);
									if (keystroke.key.keysym.sym == SDLK_SPACE) {
										step = 1;
										counter = 341;
										fadecounter = 255;
									}
								}
							}
							if (animcounter < 59)
								animcounter ++;
							else
								animcounter = 0;
							/* Show animations */
							/* Hero */
							srcblocks.y = 32;
							srcblocks.x = (animcounter / 30) * 16 + 96;
							destblocks.x = 120;
							destblocks.y = 45;
							SDL_BlitSurface(blocks,&srcblocks,window,&destblocks);
							/* Demon */
							srcblocks.y = 16;
							srcblocks.x = (animcounter / 30) * 32 + 96;
							destblocks.x = 20;
							destblocks.y = 192;
							SDL_BlitSurface(blocks,&srcblocks,window,&destblocks);
							/* Ogre */
							srcblocks.x = (animcounter / 30) * 16 + 64;
							destblocks.y = 160;
							SDL_BlitSurface(blocks,&srcblocks,window,&destblocks);
							/* Ghost */
							srcblocks.x = (animcounter / 30) * 16 + 32;
							destblocks.y = 128;
							SDL_BlitSurface(blocks,&srcblocks,window,&destblocks);
							/* Slime */
							srcblocks.x = (animcounter / 30) * 16;
							destblocks.y = 96;
							SDL_BlitSurface(blocks,&srcblocks,window,&destblocks);
							if ((counter > 1387) && (counter < 1473))
								fadecounter-=3;
							if ((counter > 1387) && (counter < 1989)) {
								srctext.y = 224;
								srctext.h = 20;
								destext.h = 20;
								SDL_BlitSurface(startinfo,&srctext,window,&destext);
								SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
								SDL_BlitSurface(blackbox,&srcscreen,window,&destscreen);
							}
							if ((counter > 1988) && (counter < 2590)) {
								srctext.y = 244;
								srctext.h = 21;
								destext.h = 21;
								SDL_BlitSurface(startinfo,&srctext,window,&destext);
							}
							if ((counter > 2589) && (counter < 3275)) {
								srctext.y = 265;
								SDL_BlitSurface(startinfo,&srctext,window,&destext);
							}
							if ((counter > 3190) && (counter < 3275)) {
								fadecounter += 3;
								SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
								SDL_BlitSurface(blackbox,&srcscreen,window,&destscreen);
							}
							if (counter == 3274) {
								step = 0;
								counter = 0;
								animcounter = 0;
							}
							break;
			case 3: /* show menu */
							SDL_BlitSurface(menu,NULL,window,NULL);
							if (posarrow == 0)
								desarrow.y = 88;
							else
								desarrow.y = 104;
							SDL_BlitSurface(arrow,&srcarrow,window,&desarrow);
							while (SDL_PollEvent(&keystroke)) {
								if (keystroke.type == SDL_QUIT)
									exit(0);
								if (keystroke.type == SDL_KEYDOWN) {
									if (keystroke.key.keysym.sym == SDLK_ESCAPE)
										exit(0);
									if ((keystroke.key.keysym.sym == SDLK_UP) || (keystroke.key.keysym.sym == SDLK_DOWN)) {
										if (posarrow == 0)
											posarrow = 1;
										else
											posarrow = 0;
									}
									if ((keystroke.key.keysym.sym == SDLK_SPACE) || (keystroke.key.keysym.sym == SDLK_RETURN)) {
										if (posarrow == 0) {
											*state = 1;
											*level = 1;
										}
										if (posarrow == 1)
											step = 4;
									}
								}
							}
							break;
			case 4: /* show password selection */
							SDL_BlitSurface(passwords,&srcscreen,window,&destscreen);
							SDL_BlitSurface(passwords,&srcselector,window,&destselector);
							while (SDL_PollEvent(&keystroke)) {
								if (keystroke.type == SDL_QUIT)
									exit(0);
								if (keystroke.type == SDL_KEYDOWN) {
									if (keystroke.key.keysym.sym == SDLK_ESCAPE)
										exit(0);
									if (keystroke.key.keysym.sym == SDLK_RIGHT) {
										if (destselector.x < 173) {
											destselector.x += 16;
											selectorpos ++;
										}
										else {
											destselector.x -= 112;
											selectorpos -= 7;
										}
									}
									if (keystroke.key.keysym.sym == SDLK_LEFT) {
										if (destselector.x > 61) {
											destselector.x -= 16;
											selectorpos --;
										}
										else {
											destselector.x += 112;
											selectorpos += 7;
										}
									}
									if (keystroke.key.keysym.sym == SDLK_UP) {
										if (destselector.y > 101) {
											destselector.y -= 16;
											selectorpos -= 8;
										}
										else {
											destselector.y += 64;
											selectorpos += 32;
										}
									}
									if (keystroke.key.keysym.sym == SDLK_DOWN) {
										if (destselector.y < 165) {
											destselector.y += 16;
											selectorpos += 8;
										}
										else {
											destselector.y -= 64;
											selectorpos -= 32;
										}
									}
									if (keystroke.key.keysym.sym == SDLK_SPACE) {
										if (selectorpos < 38) {
											passint[n] = selectorpos;
											n ++;
										}
									}
								}
							}
							/* Showing characters */
							for (i=0;i<8;i++) {

							}
							break;
		}
		/* Zoom 2x */
		doble = zoomSurface(window,2,2,0);
		SDL_BlitSurface(doble,NULL,screen,NULL);
		SDL_Flip(screen);
		SDL_FreeSurface(doble);
		SDL_FreeSurface(screen);
		control_frames(2,framerate);
	}

	/* Cleaning */
	SDL_FreeSurface(karoshi);
	SDL_FreeSurface(blackbox);
	SDL_FreeSurface(blocks);
	SDL_FreeSurface(startscreen);
	SDL_FreeSurface(startinfo);
	SDL_FreeSurface(passwords);

}