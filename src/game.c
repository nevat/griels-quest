/* game.c */

# include "game.h"

void game (SDL_Window *screen, uint8_t *state, uint8_t *level) {

    // Textures
    SDL_Texture *roundscreen = IMG_LoadTexture(renderer,"png/round.png");
    SDL_Texture *blocks = IMG_LoadTexture(renderer,"png/blocks.png");
    SDL_Texture *headgame = IMG_LoadTexture(renderer,"png/gamehead.png");
    SDL_Texture *fonts = IMG_LoadTexture(renderer,"png/fonts.png");
    SDL_Texture *blackbox = IMG_LoadTexture(renderer,"png/blackbox.png");
    SDL_Texture *gameoverscreen = IMG_LoadTexture(renderer,"png/gameover.png");
    SDL_Texture *passscreen01 = IMG_LoadTexture(renderer,"png/passw1.png");
    SDL_Texture *passscreen02 = IMG_LoadTexture(renderer,"png/passw2.png");
    SDL_Texture *passscreen03 = IMG_LoadTexture(renderer,"png/passw3.png");
    SDL_Texture *passscreen04 = IMG_LoadTexture(renderer,"png/passw4.png");
    SDL_Texture *passscreen05 = IMG_LoadTexture(renderer,"png/passw5.png");
    SDL_Texture *passscreen06 = IMG_LoadTexture(renderer,"png/passw6.png");
    SDL_Texture *passscreen07 = IMG_LoadTexture(renderer,"png/passw7.png");
    SDL_Texture *passscreen08 = IMG_LoadTexture(renderer,"png/passw8.png");
    SDL_Texture *passscreen09 = IMG_LoadTexture(renderer,"png/passw9.png");
    SDL_Texture *passscreen10 = IMG_LoadTexture(renderer,"png/passw10.png");

    // Music & sounds
    Mix_Music *bsogame;
    Mix_Music *gameover = Mix_LoadMUS(DATADIR "/music/gameover.ogg");
    Mix_Chunk *stageclear = Mix_LoadWAV(DATADIR "/music/stageclear.ogg");
    Mix_Chunk *giveup = Mix_LoadWAV(DATADIR "/fx/fx_giveup.ogg");
    Mix_Chunk *key = Mix_LoadWAV(DATADIR "/fx/fx_key.ogg");
    Mix_Chunk *kill = Mix_LoadWAV(DATADIR "/fx/fx_kill.ogg");

    uint8_t map[58][11][16]; // Map variable

    // variables
    uint8_t step = 0;
    uint16_t waittime = 0;
    uint16_t fadecounter = 0;
    uint8_t fademode = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t round = (*level - 1);
    uint16_t points = 0;
    uint8_t counter = 0;
    uint8_t animationtime = 0;
    uint8_t pausa = 0;
    uint8_t loadoninit = 0;
    uint8_t uplife = 0;
    uint8_t soundblock = 0;
    uint8_t grieltouch = 0;
    uint8_t fullscreench = 0;

    loaddata(map); // load map data

    // Enable repeat keys: Not available in SDL2
    // SDL_EnableKeyRepeat(30, 30);

    // init array
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
      .grial = 0,
    };

    // Rects
    SDL_Rect srcfonts = {0,128,8,8};
    SDL_Rect desfonts = {136,96,8,8};
    SDL_Rect srcblocks = {0,0,16,16};
    SDL_Rect desblocks = {0,0,16,16};
    SDL_Rect srctext = {0,0,256,0};

    while (*state == 2) {
        SDL_RenderClear(renderer);
	    if (counter < 58)
	      counter ++;
	    else
	      counter = 0;
	    switch (step) {
	      case 0: // Show round screen
	        *level = round + 1;
	        desfonts.x = 144;
	        SDL_SetTextureAlphaMod(roundscreen,fadecounter);
	        SDL_SetTextureAlphaMod(fonts,fadecounter);
	        SDL_RenderCopy(renderer,roundscreen,NULL,NULL);
	        if (*level < 10) {
		        srcfonts.x = 0;
		        SDL_RenderCopy(renderer,fonts,&srcfonts,&desfonts);
		        srcfonts.x = *level * 8;
		        desfonts.x = 152;
		        SDL_RenderCopy(renderer,fonts,&srcfonts,&desfonts);
	        }
	        else {
		        srcfonts.x = (*level / 10) * 8;
		        SDL_RenderCopy(renderer,fonts,&srcfonts,&desfonts);
		        srcfonts.x = (*level - ((*level / 10) * 10)) * 8;
		        desfonts.x = 152;
		        SDL_RenderCopy(renderer,fonts,&srcfonts,&desfonts);
	        }
	        if ((fademode == 0) && (fadecounter == 255))
		  SDL_EventState(SDL_KEYDOWN, SDL_IGNORE); // Disable push keys until game start
	        if ((fademode == 0) && (fadecounter < 255))
		  fadecounter += 3;
	        if ((fademode == 1) && (fadecounter > 0))
		  fadecounter -= 3;
	        if ((fademode == 0) && (fadecounter == 255)) {
	          if (waittime < 120)
	            waittime ++;
	          else {
		    fademode = 1;
		    waittime = 0;
		  }
		}
	        if ((fademode == 1) && (fadecounter == 0)) {
	          if (waittime < 60)
		        waittime ++;
	          else {
	            step = 1;
	            waittime = 0;
	            loadoninit = 1;
	            fademode = 0;
	            SDL_EventState(SDL_KEYDOWN, SDL_ENABLE); // Enable pushes keys
	          }
	        }
	      break;
	        case 1: // If stage starts now, load music
	          if (loadoninit == 1) {
	            load_music(bsogame,round);
	            loadoninit = 0;
	            set_hero_init (&griel, round);
	          }
	          // If hero have killed, reload map
	          if (griel.killed == 1) {
	            loaddata(map);
	            griel.killed = 0;
	          }
	          // When hero exits, play stage clear sound
	          if (waittime == 1)
	            Mix_PlayChannel(-1,stageclear,0);
	          // Checking score for extra life (every 5000 points), 4 lifes max.
	          extralife (&griel, &uplife);
	          // Show game screen
	          SDL_RenderCopy(renderer,headgame,NULL,NULL);
	          // Show hud
	          show_hud (griel, fonts, blocks, round);
	          // Show titles
	          show_tiles (&griel, &animationtime, map, blocks, round, counter, key);
	          // check for obstacles
	          check_obstacles (&griel, round, map, kill, &grieltouch);
	          // Griel touched ?
	          if (grieltouch == 1)
	            *state = 3;
	          // Show hero
	          show_hero(&griel, counter, blocks, &round, &step, &waittime, &soundblock, giveup);
	          // Key pressed
	          controls(&griel,&fullscreench);
	          if (fullscreench == 1) {
	              SDL_SetWindowFullscreen(screen, fullscreench ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		          fullscreench = 0;
	          }
	        break;
                case 2: // gameover screen for 10 seconds
                  if (waittime < 600) {
                    waittime ++;
                    SDL_RenderCopy(renderer,gameoverscreen,NULL,NULL);
                    if (waittime == 1)
                      Mix_PlayMusic(gameover, 0);
                  }
                  else {
                    *state = 0;
                    Mix_HaltMusic();
                  }
                break;
	        case 3: // show password info, with fade in & out
	          if (round == 4) {
                    SDL_SetTextureAlphaMod(passscreen01,fadecounter);
	                SDL_RenderCopy(renderer,passscreen01,NULL,NULL);
	          }
	          if (round == 9) {
                    SDL_SetTextureAlphaMod(passscreen02,fadecounter);
	                SDL_RenderCopy(renderer,passscreen02,NULL,NULL);
	          }
	          if (round == 14) {
                    SDL_SetTextureAlphaMod(passscreen03,fadecounter);
	                SDL_RenderCopy(renderer,passscreen03,NULL,NULL);
	          }
	          if (round == 19) {
                    SDL_SetTextureAlphaMod(passscreen04,fadecounter);
	                SDL_RenderCopy(renderer,passscreen04,NULL,NULL);
	          }
	          if (round == 24) {
                    SDL_SetTextureAlphaMod(passscreen05,fadecounter);
	                SDL_RenderCopy(renderer,passscreen05,NULL,NULL);
	          }
	          if (round == 29) {
                    SDL_SetTextureAlphaMod(passscreen06,fadecounter);
	                SDL_RenderCopy(renderer,passscreen06,NULL,NULL);
	          }
	          if (round == 35) {
                    SDL_SetTextureAlphaMod(passscreen07,fadecounter);
	                SDL_RenderCopy(renderer,passscreen07,NULL,NULL);
	          }
	          if (round == 41) {
                    SDL_SetTextureAlphaMod(passscreen08,fadecounter);
	                SDL_RenderCopy(renderer,passscreen08,NULL,NULL);
	          }
	          if (round == 47) {
                    SDL_SetTextureAlphaMod(passscreen09,fadecounter);
	                SDL_RenderCopy(renderer,passscreen09,NULL,NULL);
	          }
	          if (round == 53) {
                    SDL_SetTextureAlphaMod(passscreen10,fadecounter);
	                SDL_RenderCopy(renderer,passscreen10,NULL,NULL);
	          }
	          if ((fademode == 0) && (fadecounter == 255))
	            SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
	          if ((fademode == 0) && (fadecounter > 0))
	            fadecounter += 3;
	          if ((fademode == 1) && (fadecounter < 255))
	            fadecounter -= 3;
	          if ((fademode == 0) && (fadecounter == 0))
	            waittime ++;
	          if (((fademode == 0) && (fadecounter == 0)) && (waittime == 600))
	            fademode = 1;
	          if (waittime > 599) {
	            round ++;
	            waittime = 0;
	            step = 0;
	            fademode = 0;
	          }
	        break;
	    }

	  SDL_RenderPresent(renderer);

	}

    // Cleaning
    SDL_DestroyTexture(roundscreen);
    SDL_DestroyTexture(blocks);
    SDL_DestroyTexture(headgame);
    SDL_DestroyTexture(fonts);
    SDL_DestroyTexture(blackbox);
    // SDL_DestroyTexture(window);
    SDL_DestroyTexture(gameoverscreen);
    SDL_DestroyTexture(passscreen01);
    SDL_DestroyTexture(passscreen02);
    SDL_DestroyTexture(passscreen03);
    SDL_DestroyTexture(passscreen04);
    SDL_DestroyTexture(passscreen05);
    SDL_DestroyTexture(passscreen06);
    SDL_DestroyTexture(passscreen07);
    SDL_DestroyTexture(passscreen08);
    SDL_DestroyTexture(passscreen09);
    SDL_DestroyTexture(passscreen10);
    // Mix_FreeMusic(bsogame);
    Mix_FreeMusic(gameover);
    Mix_FreeChunk(stageclear);
    Mix_FreeChunk(giveup);
    Mix_FreeChunk(key);
    Mix_FreeChunk(kill);

}

void show_tiles (struct hero *griel, uint8_t *animationtime, uint8_t map[][11][16], SDL_Texture *blocks, uint8_t round, uint8_t counter, Mix_Chunk *key) {

  SDL_Rect srcblocks = {0,0,16,16};
  SDL_Rect desblocks = {0,0,16,16};

  uint8_t i = 0;
  uint8_t j = 0;

  for (i=0;i<11;i++) {
    for (j=0;j<16;j++) {
      if (map[round][i][j] > 0) {
        if (((map[round][i][j] == 11) || (map[round][i][j] == 13) || (map[round][i][j] == 15)) && (counter > 29))
          map[round][i][j] ++;
        if (((map[round][i][j] == 12) || (map[round][i][j] == 14) || (map[round][i][j] == 16)) && (counter < 30))
          map[round][i][j] --;
        if ((map[round][i][j] == 17) && (counter > 29))
          map[round][i][j] += 2;
        if ((map[round][i][j] == 19) && (counter < 30))
          map[round][i][j] -= 2;
        if ((map[round][i][j] == 25) && (griel->key == 1)) { // Got key, so open the door
          Mix_PlayChannel(-1,key,0);
          griel->key = 0;
          map[round][i][j] = 26;
        }
        if (map[round][i][j] == 35) { // Pow tile 2
          if (*animationtime < 15)
            *animationtime += 1;
          else {
            map[round][i][j] = 0;
            *animationtime = 0;
          }
        }
        if (map[round][i][j] == 36) { // Pow tile 1
          if (*animationtime < 15)
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
        SDL_RenderCopy(renderer,blocks,&srcblocks,&desblocks);
      }
    }
  }

}

void check_obstacles (struct hero *griel, uint8_t round, uint8_t map[][11][16], Mix_Chunk *kill, uint8_t *grieltouch) {

  int deleteobject = 0;
  int target[2] = {0,0};

  if (griel->locked == 1) {
    // Set block to analyze
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
    // Check if its a wall
    if (((target[0] > 0) && (target[0] < 4)) || ((target[0] > 7) && (target[0] < 11)) || ((target[0] > 34) && (target[0] < 37)) || ((target[0] > 40) && (target[0] < 46)) || (target[0] == 25) || (target[0] == 99)) {
      griel->locked = 0;
      /* griel->direction = 2; */
    }
    // Check for "arrow" tile
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
      // Block movement if a object is after the arrow and Griel has a object
        griel->locked = 0;
        /* griel->direction = 2; */
      }
    }
    // Check if its a enemy
    if ((target[0] == 11) || (target[0] == 12)) { // Slim
      if (griel->object == 1) {
        Mix_PlayChannel(-1,kill,0);
        deleteobject = 1;
        griel->object = 0;
        griel->score += 10;
      }
      else {
        griel->locked = 0;
        /* griel->direction = 2; */
      }
    }
    if ((target[0] == 13) || (target[0] == 14)) { // Ghost
      if (griel->object == 2) {
        deleteobject = 1;
        Mix_PlayChannel(-1,kill,0);
        griel->object = 0;
        griel->score += 60;
      }
      else {
        griel->locked = 0;
        /* griel->direction = 2; */
      }
    }
    if ((target[0] == 15) || (target[0] == 16)) { // Ogre
      if (griel->object == 3) {
        deleteobject = 1;
        Mix_PlayChannel(-1,kill,0);
        griel->object = 0;
        griel->score += 30;
      }
      else {
        griel->locked = 0;
        /* griel->direction = 2; */
      }
    }
    // Check if its a object
    if ((target[0] > 20) && (target[0] < 24)) {
      if (griel->object == 0) {
        griel->object = target[0] - 20;
        // Add points to score
        griel->score += 50;
        deleteobject = 1;
      }
      else {
        griel->locked = 0;
        /* griel->direction = 2; */
      }
    }
    if (target[0] == 24) { // Key
      griel->key = 1;
      griel->score += 300; // Add to score
      deleteobject = 1;
    }
    if (target[0] == 46) { // Grial
      griel->grial = 1;
      griel->score += 1000; // Add to score
      deleteobject = 1;
      *grieltouch = 1;
    }
    // Deleting objects
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

  // Contine moving if you are in arrow
  if (((map[round][griel->positiony][griel->positionx] > 3) && (map[round][griel->positiony][griel->positionx] < 8)) && (griel->movement == 0)) {
    griel->locked = 1;
    griel->direction = map[round][griel->positiony][griel->positionx] - 3;
  }

  // Check for a open door
  if ((map[round][griel->positiony][griel->positionx] == 26) && (griel->locked == 0)) {
    griel->direction = 5;
    griel->locked = 1;
  }

}

void controls (struct hero *griel, uint8_t *fullscreench) {

  SDL_Event keystroke;

  while (SDL_PollEvent(&keystroke)) {
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
      if (keystroke.key.keysym.sym == SDLK_f)
        *fullscreench = 1;
      if (keystroke.key.keysym.sym == SDLK_q)
        exit(0);
    }
  }

}
