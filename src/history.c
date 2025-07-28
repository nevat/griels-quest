/* history.c */

# include "history.h"

void history (SDL_Window *screen, uint8_t *state) {

  // Textures
  SDL_Texture *pictures = IMG_LoadTexture(renderer,DATADIR "/png/howtoplay.png");
  SDL_Texture *blackbox = IMG_LoadTexture(renderer,DATADIR "/png/blackbox.png");
  SDL_Texture *texts = IMG_LoadTexture(renderer,DATADIR "/png/texts.png");

  SDL_Event keystroke; // Keyboard

  Mix_Music *bso = Mix_LoadMUS(DATADIR "/music/history.ogg"); // Music
  Mix_Chunk *lol = Mix_LoadWAV(DATADIR "/fx/fx_hahaha.ogg"); // Sound

  //Variables
  uint8_t step = 0;
  uint8_t direction = 0;
  uint16_t waittime = 0;
  // uint [4] = {0,0,0,0};
  uint8_t playmusic = 0;

  // Rects
  SDL_Rect srctitle = {0,0,256,16};
  SDL_Rect destitle = {0,104,256,16};
  SDL_Rect srcblackbox = {0,0,256,224};
  SDL_Rect desblackbox = {0,0,256,224};
  SDL_Rect srcpicture = {0,0,128,64};
  SDL_Rect despicture = {64,35,128,64};
  SDL_Rect srcsent1 = {0,16,0,8};
  SDL_Rect srcsent2 = {0,32,0,8};
  SDL_Rect srcsent3 = {0,48,0,8};
  SDL_Rect srcsent4 = {0,64,0,8};
  SDL_Rect destsent1 = {28,120,0,8};
  SDL_Rect destsent2 = {28,136,0,8};
  SDL_Rect destsent3 = {28,152,0,8};
  SDL_Rect destsent4 = {28,168,0,8};

  // Loop
  
  SDL_RenderClear(renderer);
  
  while (*state == 1) {
    while (SDL_PollEvent(&keystroke)) {
      if (keystroke.type == SDL_QUIT)
        exit(0);
      if (keystroke.type == SDL_KEYDOWN) {
        if (keystroke.key.keysym.sym == SDLK_ESCAPE)
          exit(0);
        if (keystroke.key.keysym.sym == SDLK_SPACE)
          *state = 2;
      }
    }
    switch (step) {
      case 0: // show title
        if (direction == 0) {
          if (desblackbox.x < 256)
            desblackbox.x += 2;
          else
            direction = 1;
        }
        if (direction == 1) {
          if (waittime < 120)
            waittime ++;
          else {
            waittime = 0;
            direction = 2;
          }
        }
        if (direction == 2) {
          if (desblackbox.x > 0)
            desblackbox.x -= 2;
          else {
            step = 1;
            waittime = 0;
          }
        }
        SDL_RenderCopy(renderer,texts,&srctitle,&destitle);
        SDL_RenderCopy(renderer,blackbox,&srcblackbox,&desblackbox);
      break;
      case 1: // show history 1
        if (waittime == 60) // Demon LOLed
          Mix_PlayChannel(0,lol,0);
        if ((playmusic == 0) && (waittime == 180)) {
          playmusic = 1;
          Mix_PlayMusic(bso,0);
        }
        SDL_RenderCopy(renderer,blackbox,NULL,NULL);
        SDL_RenderCopy(renderer,pictures,&srcpicture,&despicture);
        if (waittime < 180)
          waittime ++;
        if (waittime > 179) {
          if (srcsent1.w < 200) {
            srcsent1.w += 1;
            destsent1.w = srcsent1.w;
          }
          SDL_RenderCopy(renderer,texts,&srcsent1,&destsent1);
          if (srcsent1.w == 200) {
            if (srcsent2.w < 200) {
              srcsent2.w += 1;
              destsent2.w = srcsent2.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent2,&destsent2);
          }
          if (srcsent2.w == 200) {
            if (srcsent3.w < 200) {
              srcsent3.w += 1;
              destsent3.w = srcsent3.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent3,&destsent3);
          }
          if (srcsent3.w == 200) {
            if (srcsent4.w < 200) {
              srcsent4.w += 1;
              destsent4.w = srcsent4.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent4,&destsent4);
          }
          if (srcsent4.w == 200) {
            if (waittime < 600)
              waittime ++;
            else {
              step = 2;
              waittime = 0;
              srcpicture.y = 64;
              srcsent1.y=72;
              srcsent2.y=88;
              srcsent3.y=104;
              srcsent4.y=120;
              srcsent1.w=0;
              srcsent2.w=0;
              srcsent3.w=0;
              srcsent4.w=0;
              destsent1.x=18;
              destsent2.x=18;
              destsent3.x=18;
              destsent4.x=18;
            }
          }
        }
        break;
        case 2: // show history 2
          SDL_RenderCopy(renderer,blackbox,NULL,NULL);
          SDL_RenderCopy(renderer,pictures,&srcpicture,&despicture);
          if (srcsent1.w < 215) {
            srcsent1.w += 1;
            destsent1.w = srcsent1.w;
          }
          SDL_RenderCopy(renderer,texts,&srcsent1,&destsent1);
          if (srcsent1.w == 215) {
            if (srcsent2.w < 215) {
              srcsent2.w += 1;
              destsent2.w = srcsent2.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent2,&destsent2);
          }
          if (srcsent2.w == 215) {
            if (srcsent3.w < 215) {
              srcsent3.w += 1;
              destsent3.w = srcsent3.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent3,&destsent3);
          }
          if (srcsent3.w == 215) {
            if (srcsent4.w < 215) {
              srcsent4.w += 1;
              destsent4.w = srcsent4.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent4,&destsent4);
          }
          if (srcsent4.w == 215) {
            if (waittime < 420)
              waittime ++;
            else {
              step = 3;
              waittime = 0;
              srcpicture.y = 128;
              srcsent1.y=128;
              srcsent2.y=144;
              srcsent3.y=160;
              srcsent4.y=176;
              srcsent1.w=0;
              srcsent2.w=0;
              srcsent3.w=0;
              srcsent4.w=0;
            }
          }
        break;
        case 3: // show history 3
          SDL_RenderCopy(renderer,blackbox,NULL,NULL);
          SDL_RenderCopy(renderer,pictures,&srcpicture,&despicture);
          if (srcsent1.w < 215) {
            srcsent1.w += 1;
            destsent1.w = srcsent1.w;
          }
          SDL_RenderCopy(renderer,texts,&srcsent1,&destsent1);
          if (srcsent1.w == 215) {
            if (srcsent2.w < 215) {
              srcsent2.w += 1;
              destsent2.w = srcsent2.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent2,&destsent2);
          }
          if (srcsent2.w == 215) {
            if (srcsent3.w < 215) {
              srcsent3.w += 1;
              destsent3.w = srcsent3.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent3,&destsent3);
          }
          if (srcsent3.w == 215) {
            if (srcsent4.w < 215) {
              srcsent4.w += 1;
              destsent4.w = srcsent4.w;
            }
            SDL_RenderCopy(renderer,texts,&srcsent4,&destsent4);
          }
          if (srcsent4.w == 215) {
            if (waittime < 420)
              waittime ++;
            else {
              *state = 2;
              Mix_HaltMusic();
            }
          }
        break;
    }

    SDL_RenderPresent(renderer);

  }

  // Cleaning
  SDL_DestroyTexture(pictures);
  SDL_DestroyTexture(blackbox);
  SDL_DestroyTexture(texts);
  Mix_FreeMusic(bso);
  Mix_FreeChunk(lol);

}
