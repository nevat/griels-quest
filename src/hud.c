/* hud.c */

# include "hud.h"

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