/* hero.c */

# include "hero.h"

void set_hero_init (struct hero *griel, int round) {

	switch (round) {
		case 0: griel->positionx = 7;
						griel->positiony = 1;
						griel->endanimation = 0;
						break;
		case 1: griel->positionx = 7;
						griel->positiony = 1;
						break;
		case 2: griel->positionx = 7;
						griel->positiony = 0;
						break;
		case 3: griel->positionx = 15;
						griel->positiony = 0;
						break;
		case 4: griel->positionx = 7;
						griel->positiony = 0;
						break;
		case 5: griel->positionx = 13;
						griel->positiony = 5;
						break;
		case 6: griel->positionx = 10;
						griel->positiony = 0;
						break;
		case 7: griel->positionx = 1;
						griel->positiony = 2;
						break;
		case 8: griel->positionx = 0;
						griel->positiony = 0;
						break;
		case 9: griel->positionx = 0;
						griel->positiony = 11;
						break;
		case 10: griel->positionx = 0;
						 griel->positiony = 11;
						 break;
		case 11: griel->positionx = 6;
						 griel->positiony = 11;
						 break;
		case 12: griel->positionx = 14;
						 griel->positiony = 5;
						 break;
		case 13: griel->positionx = 15;
						 griel->positiony = 0;
						 break;
		case 14: griel->positionx = 7;
						 griel->positiony = 5;
						 break;
		case 15: griel->positionx = 15;
						 griel->positiony = 6;
						 break;
		case 16: griel->positionx = 4;
						 griel->positiony = 10;
						 break;
		case 17: griel->positionx = 7;
						 griel->positiony = 6;
						 break;
		case 18: griel->positionx = 1;
						 griel->positiony = 1;
						 break;
		case 19: griel->positionx = 7;
						 griel->positiony = 1;
						 break;
		case 20: griel->positionx = 7;
						 griel->positiony = 5;
						 break;
		case 21: griel->positionx = 15;
						 griel->positiony = 9;
						 break;
		case 22: griel->positionx = 4;
						 griel->positiony = 4;
						 break;
		case 23: griel->positionx = 1;
						 griel->positiony = 4;
						 break;
		case 24: griel->positionx = 3;
						 griel->positiony = 10;
						 break;
		case 25: griel->positionx = 0;
						 griel->positiony = 0;
						 break;
		case 26: griel->positionx = 4;
						 griel->positiony = 2;
						 break;
		case 27: griel->positionx = 15;
						 griel->positiony = 0;
						 break;
		case 28: griel->positionx = 6;
						 griel->positiony = 5;
						 break;
		case 29: griel->positionx = 7;
						 griel->positiony = 9;
						 break;
		case 30: griel->positionx = 13;
						 griel->positiony = 8;
						 break;
		case 31: griel->positionx = 0;
						 griel->positiony = 1;
						 break;
		case 32: griel->positionx = 13;
						 griel->positiony = 8;
						 break;
		case 33: griel->positionx = 7;
						 griel->positiony = 1;
						 break;
		case 34: griel->positionx = 12;
						 griel->positiony = 8;
						 break;
		case 35: griel->positionx = 5;
						 griel->positiony = 10;
						 break;
		case 36: griel->positionx = 7;
						 griel->positiony = 0;
						 break;
		case 37: griel->positionx = 7;
						 griel->positiony = 5;
						 break;
		case 38: griel->positionx = 3;
						 griel->positiony = 1;
						 break;
		case 39: griel->positionx = 2;
						 griel->positiony = 8;
						 break;
		case 40: griel->positionx = 4;
						 griel->positiony = 0;
						 break;
		case 41: griel->positionx = 0;
						 griel->positiony = 0;
						 break;
		case 42: griel->positionx = 12;
						 griel->positiony = 7;
						 break;
		case 43: griel->positionx = 3;
						 griel->positiony = 3;
						 break;
		case 44: griel->positionx = 3;
						 griel->positiony = 8;
						 break;
		case 45: griel->positionx = 2;
						 griel->positiony = 8;
						 break;
		case 46: griel->positionx = 0;
						 griel->positiony = 0;
						 break;
		case 47: griel->positionx = 4;
						 griel->positiony = 2;
						 break;
		case 48: griel->positionx = 6;
						 griel->positiony = 6;
						 break;
		case 49: griel->positionx = 1;
						 griel->positiony = 0;
						 break;
		case 50: griel->positionx = 2;
						 griel->positiony = 3;
						 break;
		case 51: griel->positionx = 2;
						 griel->positiony = 5;
						 break;
		case 52: griel->positionx = 9;
						 griel->positiony = 2;
						 break;
		case 53: griel->positionx = 4;
						 griel->positiony = 2;
						 break;
		case 54: griel->positionx = 7;
						 griel->positiony = 0;
						 break;
		case 55: griel->positionx = 3;
						 griel->positiony = 9;
						 break;
		case 56: griel->positionx = 8;
						 griel->positiony = 6;
						 break;
		case 57: griel->positionx = 4;
						 griel->positiony = 9;
						 break;
	}
	griel->x = griel->positionx * 16;
	griel->y = 32 + (griel->positiony * 16);
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
					if ((*round != 4) && (*round !=10)) {
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