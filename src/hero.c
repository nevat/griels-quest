/* hero.c */

# include "hero.h"

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
		case 5: griel->x = 208;
						griel->y = 112;
						griel->positionx = 13;
						griel->positiony = 5;
						break;
		case 6: griel->x = 160;
						griel->y = 32;
						griel->positionx = 10;
						griel->positiony = 0;
						break;
		case 7: griel->x = 16;
						griel->y = 64;
						griel->positionx = 1;
						griel->positiony = 2;
						break;
		case 8: griel->x = 0;
						griel->y = 32;
						griel->positionx = 0;
						griel->positiony = 0;
						break;
		case 9: griel->x = 0;
						griel->y = 192;
						griel->positionx = 0;
						griel->positiony = 11;
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

	if (griel->locked == 1) { /* Animation if Griel is moving */
		if (((counter > 14) && (counter < 30)) || ((counter > 44) && (counter < 60)))
			srchero.x = srchero.x + 16;
	}

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
					if (*round != 4) {
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