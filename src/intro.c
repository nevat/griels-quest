/* intro.c */

# include "intro.h"

void game_intro (SDL_Window *screen, uint8_t *state, uint8_t *level) {

  // Textures
  SDL_Texture *blackbox = IMG_LoadTexture(renderer,"png/blackbox.png");
  SDL_Texture *karoshi = IMG_LoadTexture(renderer,"png/karoshi.png");
  SDL_Texture *blocks = IMG_LoadTexture(renderer,"png/blocks.png");
  SDL_Texture *startscreen = IMG_LoadTexture(renderer,"png/startscreen.png");
  SDL_Texture *startinfo = IMG_LoadTexture(renderer,"png/startinfo.png");
  SDL_Texture *menu = IMG_LoadTexture(renderer,"png/menu.png");
  SDL_Texture *arrow = IMG_LoadTexture(renderer,"png/fonts.png");
  SDL_Texture *passwords = IMG_LoadTexture(renderer,"png/password.png");
  SDL_Texture *fonts = IMG_LoadTexture(renderer,"png/fonts.png");
  
  // Sounds
  Mix_Chunk *start = Mix_LoadWAV("fx/fx_start.ogg");
  Mix_Chunk *poff = Mix_LoadWAV("fx/fx_poff.ogg");
  Mix_Chunk *error = Mix_LoadWAV("fx/fx_error.ogg");
  Mix_Chunk *ding = Mix_LoadWAV("fx/fx_ding.ogg");

  SDL_Event keystroke; // Keyboard

  // Rects
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
  SDL_Rect srcletters = {0,0,16,16};
  SDL_Rect destletters = {64,64,16,16};

  // Variables
  uint8_t step = 0;
  uint16_t counter = 0;
  uint16_t fadecounter = 0;
  uint8_t animcounter = 0;
  uint8_t posarrow = 0;
  uint8_t selectorpos = 1;
  uint8_t passint[8] = {0,0,0,0,0,0,0,0};
  uint8_t n = 0;
  uint8_t validatepass = 0;
  uint8_t i = 0;
  uint8_t result = 0;

  // Loop
  while (*state == 0) {
    SDL_RenderClear(renderer);
    switch (step) {
      case 0: // Karoshi logo
        SDL_SetTextureAlphaMod(karoshi,fadecounter);
        SDL_RenderCopy(renderer,karoshi,&srcscreen,&destscreen);
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
          fadecounter+=3;
        if ((counter > 254) && (counter < 341))
          fadecounter-=3;
        if (counter == 340) {
          step = 1;
          fadecounter = 0;
        }
      break;
      case 1: // Start screen
        SDL_SetTextureAlphaMod(startscreen,fadecounter);
        SDL_RenderCopy(renderer,startscreen,&srcscreen,&destscreen);
        counter ++;
        while (SDL_PollEvent(&keystroke)) {
          if (keystroke.type == SDL_QUIT)
            exit(0);
          if (keystroke.type == SDL_KEYDOWN) {
            if (keystroke.key.keysym.sym == SDLK_ESCAPE)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_SPACE) {
              Mix_PlayChannel(-1,start,0);
              step = 3;
            }
          }
        }
        if ((counter > 340) && (counter < 426))
          fadecounter+=3;
        if ((counter > 1325) && (counter < 1387))
          fadecounter-=3;
        if (counter == 1387) {
          step = 2;
          fadecounter = 0;
        }
      break;
      case 2: // Show instructions
        SDL_RenderCopy(renderer,startinfo,&srcscreen,&destscreen);
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
        
        // Show animations
        // Hero
        srcblocks.y = 32;
        srcblocks.x = (animcounter / 30) * 16 + 96;
        destblocks.x = 120;
        destblocks.y = 45;
        SDL_RenderCopy(renderer,blocks,&srcblocks,&destblocks);
        // Demon
        srcblocks.y = 16;
        srcblocks.x = (animcounter / 30) * 32 + 96;
        destblocks.x = 20;
        destblocks.y = 192;
        SDL_RenderCopy(renderer,blocks,&srcblocks,&destblocks);
        // Ogre
        srcblocks.x = (animcounter / 30) * 16 + 64;
        destblocks.y = 160;
        SDL_RenderCopy(renderer,blocks,&srcblocks,&destblocks);
        // Ghost
        srcblocks.x = (animcounter / 30) * 16 + 32;
        destblocks.y = 128;
        SDL_RenderCopy(renderer,blocks,&srcblocks,&destblocks);
        // Slime
        srcblocks.x = (animcounter / 30) * 16;
        destblocks.y = 96;
        SDL_RenderCopy(renderer,blocks,&srcblocks,&destblocks);
        if ((counter > 1387) && (counter < 1473))
	  fadecounter+=3;
        if ((counter > 1387) && (counter < 1989)) {
          srctext.y = 224;
          srctext.h = 20;
          destext.h = 20;
          SDL_SetTextureAlphaMod(startinfo,fadecounter);
          SDL_RenderCopy(renderer,startinfo,&srctext,&destext);
        }
        if ((counter > 1988) && (counter < 2590)) {
          srctext.y = 244;
          srctext.h = 21;
          destext.h = 21;
          SDL_RenderCopy(renderer,startinfo,&srctext,&destext);
        }
        if ((counter > 2589) && (counter < 3275)) {
          srctext.y = 265;
          SDL_RenderCopy(renderer,startinfo,&srctext,&destext);
        }
        if ((counter > 3190) && (counter < 3275)) {
          fadecounter -= 3;
          SDL_SetTextureAlphaMod(startinfo,fadecounter);
          SDL_RenderCopy(renderer,startinfo,&srcscreen,&destscreen);
        }
        if (counter == 3274) {
          step = 0;
          counter = 0;
          animcounter = 0;
        }
      break;
      case 3: // show menu
        SDL_RenderCopy(renderer,menu,NULL,NULL);
        if (posarrow == 0)
          desarrow.y = 88;
        else
          desarrow.y = 104;
        SDL_RenderCopy(renderer,arrow,&srcarrow,&desarrow);
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
              Mix_PlayChannel(-1,start,0);
            }
        }
      }
      break;
      case 4: // show password selection
        SDL_RenderCopy(renderer,passwords,&srcscreen,&destscreen);
        SDL_RenderCopy(renderer,passwords,&srcselector,&destselector);
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
	      if (selectorpos < 37) {
	        passint[n] = selectorpos;
	        if (n < 7)
	          n ++;
	        else
	          n = 1;
	        Mix_PlayChannel(-1,start,0);
	      }
	      if (selectorpos == 37) { /* Tilde */
	        passint[n] = 0;
	        if (n < 7)
	          n ++;
	        else
	          n = 1;
	        Mix_PlayChannel(-1,start,0);
	      }
	      if (selectorpos == 38) { /* Delete */
	        if (n > 0) {
	          passint[n-1] = 0;
	          n --;
	        }
	        else {
	          n = 7;
	          passint[n] = 0;
	        }
	        Mix_PlayChannel(-1,poff,0);
	      }
	      if (selectorpos == 39) /* Ok key */
	        validatepass = 1;
            }
          }
        }
        // Showing characters
        for (i=0;i<8;i++) {
          if (passint[i] > 0) {
            if (passint[i] < 11) {
              srcletters.y = 80;
              srcletters.x = (passint[i] - 1) * 16;
            }
            if ((passint[i] > 10) && (passint[n] < 21)) {
              srcletters.y = 96;
              srcletters.x = (passint[i] - 11) * 16;
            }
            if ((passint[i] > 20) && (passint[n] < 27)) {
              srcletters.y = 112;
              srcletters.x = (passint[i] - 21) * 16;
            }
            if ((passint[i] > 26) && (passint[i] <  37)) {
              srcletters.y = 64;
              srcletters.x = (passint[i] - 27) * 16;
            }
            destletters.x = 64 + (i * 16);
            destletters.y = 64;
            SDL_RenderCopy(renderer,fonts,&srcletters,&destletters);
          }
        }
        /* Showing character position */
        srcletters.x = 96;
        srcletters.y = 112;
        destletters.x = 64 + (n * 16);
        destletters.y = 80;
        SDL_RenderCopy(renderer,fonts,&srcletters,&destletters);
        /* Checking if password is correct */
        if (validatepass == 1) {
          result = passwvalidate(passint);
          validatepass = 0;
          if (result > 0) {
            *level = result;
            Mix_PlayChannel(-1,ding,0);
            *state = 2;
          }
          else
            Mix_PlayChannel(-1,error,0);
        }
        break;
    }
    
    SDL_RenderPresent(renderer);

  }

  /* Cleaning */
  SDL_DestroyTexture(karoshi);
  SDL_DestroyTexture(blackbox);
  SDL_DestroyTexture(blocks);
  SDL_DestroyTexture(startscreen);
  SDL_DestroyTexture(startinfo);
  SDL_DestroyTexture(passwords);
  SDL_DestroyTexture(fonts);
  Mix_FreeChunk(start);
  Mix_FreeChunk(poff);
  Mix_FreeChunk(error);
  Mix_FreeChunk(ding);

}

uint8_t passwvalidate (uint8_t passint[]) {

  uint8_t n = 0;

  if ((passint[0] == 7) && (passint[1] == 5) && (passint[2] == 14) && (passint[3] == 5) && (passint[4] == 19) && (passint[5] == 9) && (passint[6] == 19) && (passint[7] == 0))
    n = 6;

  if ((passint[0] == 16) && (passint[1] == 19) && (passint[2] == 1) && (passint[3] == 12) && (passint[4] == 13) && (passint[5] == 19) && (passint[6] == 0) && (passint[7] == 0))
    n = 11;

  if ((passint[0] == 18) && (passint[1] == 15) && (passint[2] == 13) && (passint[3] == 1) && (passint[4] == 14) && (passint[5] == 19) && (passint[6] == 0) && (passint[7] == 0))
    n = 16;

  if ((passint[0] == 10) && (passint[1] == 1) && (passint[2] == 13) && (passint[3] == 5) && (passint[4] == 19) && (passint[5] == 0) && (passint[6] == 0) && (passint[7] == 0))
    n = 21;

  if ((passint[0] == 5) && (passint[1] == 3) && (passint[2] == 3) && (passint[3] == 12) && (passint[4] == 5) && (passint[5] == 9) && (passint[6] == 1) && (passint[7] == 0))
    n = 26;

  if ((passint[0] == 8) && (passint[1] == 5) && (passint[2] == 2) && (passint[3] == 18) && (passint[4] == 5) && (passint[5] == 23) && (passint[6] == 19) && (passint[7] == 0))
    n = 31;

  if ((passint[0] == 10) && (passint[1] == 15) && (passint[2] == 8) && (passint[3] == 14) && (passint[4] == 0) && (passint[5] == 0) && (passint[6] == 0) && (passint[7] == 0))
    n = 37;

  if ((passint[0] == 16) && (passint[1] == 18) && (passint[2] == 15) && (passint[3] == 22) && (passint[4] == 5) && (passint[5] == 18) && (passint[6] == 2) && (passint[7] == 19))
    n = 43;

  if ((passint[0] == 9) && (passint[1] == 19) && (passint[2] == 1) && (passint[3] == 9) && (passint[4] == 1) && (passint[5] == 8) && (passint[6] == 0) && (passint[7] == 0))
    n = 49;

  if ((passint[0] == 13) && (passint[1] == 1) && (passint[2] == 20) && (passint[3] == 20) && (passint[4] == 8) && (passint[5] == 5) && (passint[6] == 23) && (passint[7] == 0))
    n = 55;

  return n;

}
