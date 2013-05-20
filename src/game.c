/* game.c */

# include "game.h"

void game (SDL_Surface *screen, uint *state, uint *level) {

	SDL_Surface *roundscreen = NULL;
	SDL_Surface *blocks = NULL;
	SDL_Surface *temp = NULL;
	SDL_Surface *headgame = NULL;
	SDL_Surface *fonts = NULL;
	SDL_Surface *blackbox = NULL;
	SDL_Surface *window = NULL;
	SDL_Surface *doble = NULL;
	SDL_Surface *gameoverscreen = NULL;
	SDL_Surface *comingsoon = NULL;

	Mix_Music *bso;
	Mix_Music *gameover;
	Mix_Chunk *stageclear;

	int map[5][11][16];

	uint step = 0;
	uint waittime = 0;
	uint fadecounter = 255;
	int framerate = 0;
	uint fademode = 0;
	uint i = 0;
	uint j = 0;
	int round = (*level - 1);
	int points = 0;
	int counter = 0;
	int animationtime = 0;
	uint pausa = 0;
	uint loadoninit = 0;
	uint uplife = 0;

	/* load files */
	temp = IMG_Load("../png/round.png");
	roundscreen = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/blocks.png");
	blocks = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/gamehead.png");
	headgame = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/fonts.png");
	fonts = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/blackbox.png");
	blackbox = SDL_DisplayFormat(temp);
	window = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/gameover.png");
	gameoverscreen = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../png/soon.png");
	comingsoon = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	stageclear = Mix_LoadWAV("../music/stageclear.ogg");
	gameover = Mix_LoadMUS("../music/gameover.ogg");

	/* load map data */
	loaddata(map);

	/* Enable repeat keys */
	SDL_EnableKeyRepeat(30, 30);

	/* init array */
	struct hero griel = {
		.score = 0,
		.lifes = 3,
		.object = 0,
		.key = 0,
		.x = 112,
		.y = 48,
		.positionx = 7,
		.positiony = 1,
		.direction = 2,
		.locked = 0,
		.movement = 0,
		.endanimation = 0,
		.deathanimation = 0,
		.deathturns = 0,
		.killed = 0,
	};

	/* Disable push keys until game start */
	SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);

	SDL_Rect srcfonts = {0,128,8,8};
	SDL_Rect desfonts = {136,96,8,8};
	SDL_Rect srcblocks = {0,0,16,16};
	SDL_Rect desblocks = {0,0,16,16};
	SDL_Rect srctext = {0,0,256,0};

	while (*state == 2) {
		framerate = control_frames(1,0);
		if (counter < 58)
			counter ++;
		else
			counter = 0;
		switch (step) {
			case 0: /* Show round screen */
							*level = round + 1;
							desfonts.x = 144;
							SDL_BlitSurface(roundscreen,NULL,window,NULL);
							if (*level < 10) {
								srcfonts.x = 0;
								SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
								srcfonts.x = *level * 8;
								desfonts.x = 152;
								SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
							}
							/* Apply transparency */
							SDL_SetAlpha(blackbox,SDL_RLEACCEL|SDL_SRCALPHA,(Uint8)fadecounter);
							SDL_BlitSurface(blackbox,NULL,window,NULL);
							if ((fademode == 0) && (fadecounter > 0))
								fadecounter -= 3;
							if ((fademode == 1) && (fadecounter < 255))
								fadecounter += 3;
							if ((fademode == 0) && (fadecounter == 0))
								fademode = 1;
							if ((fademode == 1) && (fadecounter == 255))
								waittime ++;
							if (waittime == 60) {
								step = 1;
								waittime = 0;
								loadoninit = 1;
								fademode = 0;
								SDL_EventState(SDL_KEYDOWN, SDL_ENABLE); /* Enable pushes keys */
							}
							break;
			case 1: /* If stage starts now, load music */
							if (loadoninit == 1) {
								load_music(bso,round);
								loadoninit = 0;
								set_hero_init (&griel, round);
							}
							/* If hero have killed, reload map */
							if (griel.killed == 1) {
								loaddata(map);
								griel.killed = 0;
							}
							/* When hero exits, play stage clear sound */
							if (waittime == 1)
								Mix_PlayChannel(-1,stageclear,0);
							/* Checking score for extra life (every 5000 points), 4 lifes max. */
							extralife (&griel, &uplife);
							/* Show game screen */
							SDL_BlitSurface(headgame,NULL,window,NULL);
							/* Show hud */
							show_hud (griel, fonts, window, blocks, round);
							/* Show titles */
							show_tiles (&griel, &animationtime, map, window, blocks, round, counter);
							/* check for obstacles */
							check_obstacles (&griel, round, map);
							/* Show hero */
							show_hero(&griel, counter, window, blocks, &round, &step, &waittime);
							/* Key pressed */
							controls(&griel);
							break;
			case 2: /* gameover screen for 10 seconds */
							if (waittime < 600) {
								waittime ++;
								SDL_BlitSurface(gameoverscreen,NULL,window,NULL);
								if (waittime == 1)
									Mix_PlayMusic(gameover, 0);
							}
							else {
								*state = 0;
								Mix_HaltMusic();
							}
							break;
			case 3: /* show "comming soon" screen and return */
							if (waittime < 900) {
								waittime ++;
								if (waittime == 1)
									Mix_PlayMusic(gameover, 0);
								if (waittime < 300)
									srctext.h = 57;
								else
									srctext.h = 224;
								SDL_BlitSurface(blackbox,NULL,window,NULL);
								SDL_BlitSurface(comingsoon,&srctext,window,NULL);
							}
							else {
								*state = 0;
								Mix_HaltMusic();
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
	SDL_FreeSurface(roundscreen);
	SDL_FreeSurface(blocks);
	SDL_FreeSurface(headgame);
	SDL_FreeSurface(fonts);
	SDL_FreeSurface(blackbox);
	SDL_FreeSurface(window);
	SDL_FreeSurface(gameoverscreen);
	/* BUG: if bso music is cleared, segmentation fault occurs, i don't know why */
	/* Mix_FreeMusic(bso); */
	Mix_FreeMusic(gameover);
	Mix_FreeChunk(stageclear);

}

void loaddata (int map[][11][16]) {

	uint i = 0;
	uint j = 0;
	uint k = 0;
	FILE *datafile = fopen("../data/rounds.txt", "r");
	char line[49];
	char temp[2];;

	/* Load data an put in array */
	fgets (line, 49, datafile);
	for (i=0;i<5;i++) {
		for (j=0;j<11;j++) {
			for (k=0;k<16;k+=1) {
				temp[0] = line[k*3];
				temp[1] = line[k*3 + 1];
				sscanf (temp, "%d", &map[i][j][k]);
			}
			fgets (line, 49, datafile);
		}
		fgets (line, 49, datafile);
	}

	fclose(datafile);

}

void show_hud (struct hero griel, SDL_Surface *fonts, SDL_Surface *window, SDL_Surface *blocks, int round) {

	SDL_Rect srcfonts = {0,128,8,8};
	SDL_Rect desfonts = {136,96,8,8};
	SDL_Rect srcblocks = {0,0,16,16};
	SDL_Rect desblocks = {0,0,16,16};

	int points = 0;
	int i = 0;

	/* Show score */
	/* Can be optimized ? */
	points = griel.score;
	desfonts.x = 16;
	desfonts.y = 8;
	if (points > 999999) {
		srcfonts.x = (points / 1000000) * 8;
		points -= ((srcfonts.x / 8) * 1000000);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 24;
	if (points > 99999) {
		srcfonts.x = (points / 100000) * 8;
		points -= ((srcfonts.x / 8) * 100000);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 32;
	if (points > 9999) {
		srcfonts.x = (points / 10000) * 8;
		points -= ((srcfonts.x / 8) * 10000);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 40;
	if (points > 999) {
		srcfonts.x = (points / 1000) * 8;
		points -= ((srcfonts.x / 8) * 1000);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 48;
	if (points > 99) {
		srcfonts.x = (points / 100) * 8;
		points -= ((srcfonts.x / 8) * 100);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 56;
	if (points > 9) {
		srcfonts.x = (points / 10) * 8;
		points -= ((srcfonts.x / 8) * 10);
	}
	else
		srcfonts.x = 0;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	desfonts.x = 64;
	srcfonts.x = (points) * 8;
	SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);

	/* Show lifes */
	for (i=1;i<4;i++) {
		if (i < griel.lifes) {
			srcblocks.x = 96;
			srcblocks.y = 32;
			desblocks.y = 0;
			desblocks.x = 112 + (16 * i);
			SDL_BlitSurface(blocks,&srcblocks,window,&desblocks);
		}
	}

	/* Show object */
	if (griel.object > 0) {
		desblocks.x = 96;
		desblocks.y = 0;
		srcblocks.y = 32;
		srcblocks.x = 0 + (16 * griel.object) - 16;
		SDL_BlitSurface(blocks,&srcblocks,window,&desblocks);
	}

	/* Show round number */
	if ((round + 1) < 10) {
		desfonts.x = 208;
		desfonts.y = 8;
		srcfonts.x = 0;
		SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
		desfonts.x = 216;
		srcfonts.x = (round + 1) * 8;
		SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	}
	else {
		desfonts.x = 208;
		desfonts.y = 8;
		srcfonts.x = ((round + 1) / 10) * 8;
		SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
		desfonts.x = 216;
		desfonts.y = 8;
		srcfonts.x = ((((round + 1) / 10) * 10) - (round + 1)) * 8;
		SDL_BlitSurface(fonts,&srcfonts,window,&desfonts);
	}

}

void show_tiles (struct hero *griel, int *animationtime, int map[][11][16], SDL_Surface *window, SDL_Surface *blocks, int round, int counter) {

	SDL_Rect srcblocks = {0,0,16,16};
	SDL_Rect desblocks = {0,0,16,16};

	int i = 0;
	int j = 0;

	for (i=0;i<11;i++) {
		for (j=0;j<16;j++) {
			if (map[round][i][j] > 0) {
				if (((map[round][i][j] == 11) || (map[round][i][j] == 13) || (map[round][i][j] == 15)) && (counter > 29))
					map[round][i][j] ++;
				if (((map[round][i][j] == 12) || (map[round][i][j] == 14) || (map[round][i][j] == 16)) && (counter < 30))
					map[round][i][j] --;
				if ((map[round][i][j] == 25) && (griel->key == 1)) { /* Got key, so open the door */
					griel->key = 0;
					map[round][i][j] = 26;
				}
				if (map[round][i][j] == 35) { /* Pow tile 2 */
					if (*animationtime < 20)
						*animationtime += 1;
					else {
						map[round][i][j] = 0;
						*animationtime = 0;
					}
				}
				if (map[round][i][j] == 36) { /* Pow tile 1 */
					if (*animationtime < 20)
						*animationtime += 1;
					else {
						map[round][i][j] = 35;
						*animationtime = 0;
					}
				}
				srcblocks.x = (map[round][i][j] - ((map[round][i][j] / 10) * 10) - 1) * 16;
				srcblocks.y = (map[round][i][j] / 10) * 16;
				if (map[round][i][j] == 10) {
					srcblocks.x = 144;
					srcblocks.y = 0;
				}
				desblocks.x = j * 16;
				desblocks.y = (i * 16) + 32;
				SDL_BlitSurface(blocks,&srcblocks,window,&desblocks);
			}
		}
	}

}

void check_obstacles (struct hero *griel, int round, int map[][11][16]) {

	int deleteobject = 0;
	int target[2] = {0,0};

	if (griel->locked == 1) {
		/* Set block to analyze */
		switch (griel->direction) {
			case 1: target[0] = map[round][griel->positiony-1][griel->positionx];
							if (griel->positiony > 1)
								target[1] = map[round][griel->positiony-2][griel->positionx];
							else
								target[1] = 0;
							break;
			case 2: target[0] = map[round][griel->positiony+1][griel->positionx];
							if (griel->positiony < 9)
								target[1] = map[round][griel->positiony+2][griel->positionx];
							else
								target[1] = 0;
							break;
			case 3: target[0] = map[round][griel->positiony][griel->positionx-1];
							if (griel->positionx > 1)
								target[1] = map[round][griel->positiony][griel->positionx-2];
							else
								target[1] = 0;
							break;
			case 4: target[0] = map[round][griel->positiony][griel->positionx+1];
							if (griel->positionx < 14)
								target[1] = map[round][griel->positiony][griel->positionx+2];
							else
								target[1] = 0;
							break;
		}
		/* Check if its a wall */
		if (((target[0] > 0) && (target[0] < 4)) || ((target[0] > 7) && (target[0] < 11)) || ((target[0] > 34) && (target[0] < 37)) || (target[0] == 25) || (target[0] == 99)) {
			griel->locked = 0;
			/* griel->direction = 2; */
		}
		/* Check for "arrow" tile */
		if ((target[0] > 3) && (target[0] < 8)) {
			if ((griel->direction == 1) && (target[0] == 5)) {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
			if ((griel->direction == 2) && (target[0] == 4)) {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
			if ((griel->direction == 3) && (target[0] == 7)) {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
			if ((griel->direction == 4) && (target[0] == 6)) {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
			if ((griel->direction + 3 == target[0]) && ((target[1] > 20) && (target[1] < 24)) && (griel->object > 0)) {
			/* Block movement if a object is after the arrow and Griel has a object */
				griel->locked = 0;
				/* griel->direction = 2; */
			}
		}
		/* Check if its a enemy */
		if ((target[0] == 11) || (target[0] == 12)) { /* Slim */
			if (griel->object == 1) {
				deleteobject = 1;
				griel->object = 0;
				griel->score += 10;
			}
			else {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
		}
		if ((target[0] == 13) || (target[0] == 14)) { /* Ghost */
			if (griel->object == 2) {
				deleteobject = 1;
				griel->object = 0;
				griel->score += 60;
			}
			else {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
		}
		if ((target[0] == 15) || (target[0] == 16)) { /* Ogre */
			if (griel->object == 3) {
				deleteobject = 1;
				griel->object = 0;
				griel->score += 30;
			}
			else {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
		}
		/* Check if its a object */
		if ((target[0] > 20) && (target[0] < 24)) {
			if (griel->object == 0) {
				griel->object = target[0] - 20;
				/* Add points to score */
				griel->score += 50;
				deleteobject = 1;
			}
			else {
				griel->locked = 0;
				/* griel->direction = 2; */
			}
		}
		if (target[0] == 24) { /* Key */
				griel->key = 1;
				griel->score += 300; /* Add to score */
				deleteobject = 1;
		}
		/* Deleting objects */
		if (deleteobject == 1) {
			switch (griel->direction) {
				case 1: if (map[round][griel->positiony-1][griel->positionx] < 21) {
									map[round][griel->positiony-1][griel->positionx] = 36;
									griel->locked = 0;
									/* griel->direction = 2; */
								}
								else
									map[round][griel->positiony-1][griel->positionx] = 0;
								break;
				case 2: if (map[round][griel->positiony+1][griel->positionx] < 21) {
									map[round][griel->positiony+1][griel->positionx] = 36;
									griel->locked = 0;
									/* griel->direction = 2; */
								}
								else
									map[round][griel->positiony+1][griel->positionx] = 0;
								break;
				case 3: if (map[round][griel->positiony][griel->positionx-1] < 21) {
									map[round][griel->positiony][griel->positionx-1] = 36;
									griel->locked = 0;
									/* griel->direction = 2; */
								}
								else
									map[round][griel->positiony][griel->positionx-1] = 0;
								break;
				case 4: if (map[round][griel->positiony][griel->positionx+1] < 21) {
									map[round][griel->positiony][griel->positionx+1] = 36;
									griel->locked = 0;
									/* griel->direction = 2; */
								}
								else
									map[round][griel->positiony][griel->positionx+1] = 0;
								break;
			}
		}
	}

	/* Contine moving if you are in arrow */
	if (((map[round][griel->positiony][griel->positionx] > 3) && (map[round][griel->positiony][griel->positionx] < 8)) && (griel->movement == 0)) {
		griel->locked = 1;
		griel->direction = map[round][griel->positiony][griel->positionx] - 3;
	}

	/* Check for a open door */
	if ((map[round][griel->positiony][griel->positionx] == 26) && (griel->locked == 0)) {
		griel->direction = 5;
		griel->locked = 1;
	}

}

void show_hero (struct hero *griel, int counter, SDL_Surface *window, SDL_Surface *blocks, int *round, int *step, uint *waittime) {

	SDL_Rect srchero = {96,32,16,16};
	SDL_Rect desthero = {0,0,16,16};

	/* Set X & Y coord. for hero tile */
	switch (griel->direction) {
		case 1: srchero.x = 128;
						srchero.y = 32;
						break;
		case 2: srchero.x = 96;
						srchero.y = 32;
						break;
		case 3: srchero.x = 0;
						srchero.y = 48;
						break;
		case 4: srchero.x = 32;
						srchero.y = 48;
						break;
		case 5: srchero.x = 96;
						srchero.y = 48;
						break;
	}

	if (((counter > 14) && (counter < 30)) || ((counter > 44) && (counter < 60))) /* Animation */
		srchero.x = srchero.x + 16;

	/* Hero movement */
	if (griel->locked == 1) {
		if (griel->direction == 2) {
			if (griel->movement < 16) { /* down */
				griel->y ++;
				griel->movement ++;
			}
			else {
				griel->movement = 0;
				griel->locked = 0;
				griel->positiony ++;
			}
		}
		if (griel->direction == 1) {
			if (griel->movement < 16) { /* up */
				griel->y --;
				griel->movement ++;
			}
			else {
				griel->movement = 0;
				griel->locked = 0;
				griel->positiony --;
				/* griel->direction = 2; */
			}
		}
		if (griel->direction == 3) {
			if (griel->movement < 16) { /* left */
				griel->x --;
				griel->movement ++;
			}
			else {
				griel->movement = 0;
				griel->locked = 0;
				griel->positionx --;
				/* griel->direction = 2; */
			}
		}
		if (griel->direction == 4) {
			if (griel->movement < 16) { /* right */
				griel->x ++;
				griel->movement ++;
			}
			else {
				griel->movement = 0;
				griel->locked = 0;
				griel->positionx ++;
				/* griel->direction = 2; */
			}
		}
		if (griel->direction == 5) { /* Exiting stage */
			if (griel->endanimation < 80) {
				griel->endanimation += 1;
				if (griel->endanimation == 1)
					Mix_HaltMusic();
				srchero.x += (griel->endanimation / 20) * 16;
			}
			else { /* change round */
				srchero.x = 80;
				srchero.y = 32;
				if (*waittime < 220)
					*waittime += 1;
				else {
					if (*round < 4) {
						*round += 1;
						*step = 0;
						*waittime = 0;
					}
					else {
						*step = 3;
						*waittime = 0;
					}
				}
			}
		}
		if (griel->direction == 6) { /* Hero dead animation */
			if (griel->deathturns < 7) {
				switch (griel->deathanimation) {
					case 0: srchero.x = 96;
									srchero.y = 32;
									break;
					case 1: srchero.x = 0;
									srchero.y = 48;
									break;
					case 2: srchero.x = 128;
									srchero.y = 32;
									break;
					case 3: srchero.x = 32;
									srchero.y = 48;
									break;
				}
				if (griel->deathanimation < 4) {
					if (counter % 5 == 0)
						griel->deathanimation ++;
				}
				else {
					griel->deathturns ++;
					griel->deathanimation = 0;
				}
			}
			else {
				if (griel->lifes > 1) { /* -1 life, and start round again */
					griel->lifes --;
					*step = 0;
					griel->killed = 1;
				}
				else /* Call "Game Over" screen */
					*step = 2;
				Mix_HaltMusic();
			}
		}
	}
	desthero.x = griel->x;
	desthero.y = griel->y;
	SDL_BlitSurface(blocks,&srchero,window,&desthero);

}

void controls (struct hero *griel) {

	SDL_Event keystroke;

	while (SDL_PollEvent(&keystroke2)) {
		if (keystroke.type == SDL_QUIT)
			exit(0);
		if (keystroke.type == SDL_KEYDOWN) {
			if (keystroke.key.keysym.sym == SDLK_ESCAPE) {
				if ((griel->locked == 0) && (griel->deathanimation == 0)) {
					griel->locked = 1;
					griel->direction = 6;
				}
			}
			if (keystroke.key.keysym.sym == SDLK_UP) {
				if ((griel->locked == 0) && (griel->positiony > 0)) {
					griel->locked = 1;
					griel->direction = 1;
				}
			}
			if (keystroke.key.keysym.sym == SDLK_DOWN) {
				if ((griel->locked == 0) && (griel->positiony < 10)) {
					griel->locked = 1;
					griel->direction = 2;
				}
			}
			if (keystroke.key.keysym.sym == SDLK_LEFT) {
				if ((griel->locked == 0) && (griel->positionx > 0)) {
					griel->locked = 1;
					griel->direction = 3;
				}
			}
			if (keystroke.key.keysym.sym == SDLK_RIGHT) {
				if ((griel->locked == 0) && (griel->positionx < 15)) {
					griel->locked = 1;
					griel->direction = 4;
				}
			}
		}
	}

}

void load_music(Mix_Music *bso, int round) {

	if ((round == 0) || (round == 5))
		bso = Mix_LoadMUS("../music/stage1.ogg");
	if ((round == 1) || (round == 6))
		bso = Mix_LoadMUS("../music/stage2.ogg");
	if ((round == 2) || (round == 7))
		bso = Mix_LoadMUS("../music/stage3.ogg");
	if ((round == 3) || (round == 8))
		bso = Mix_LoadMUS("../music/stage4.ogg");
	if ((round == 4) || (round == 9))
		bso = Mix_LoadMUS("../music/stage5.ogg");

	Mix_PlayMusic(bso, -1);

}

void set_hero_init (struct hero *griel, int round) {

	switch (round) {
		case 0: griel->x = 112;
						griel->y = 48;
						griel->positionx = 7;
						griel->positiony = 1;
						griel->endanimation = 0;
						break;
		case 1: griel->x = 112;
						griel->y = 48;
						griel->positionx = 7;
						griel->positiony = 1;
						break;
		case 2: griel->x = 112;
						griel->y = 32;
						griel->positionx = 7;
						griel->positiony = 0;
						break;
		case 3: griel->x = 240;
						griel->y = 32;
						griel->positionx = 15;
						griel->positiony = 0;
						break;
		case 4: griel->x = 112;
						griel->y = 32;
						griel->positionx = 7;
						griel->positiony = 0;
						break;
	}
	griel->direction = 2;
	griel->locked = 0;
	griel->endanimation = 0;
	griel->deathanimation = 0;
	griel->deathturns = 0;
	griel->object = 0;

}

void extralife (struct hero *griel, uint *uplife) {

	if (griel->score > (5000 + (*uplife * 5000))) {
		*uplife += 1;
		if (griel->lifes < 4)
			griel->lifes += 1;
	}

}