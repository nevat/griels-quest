/* ending.c */

# include "ending.h"

void ending (SDL_Window *screen, uint8_t *state) {

  // Textures
  SDL_Texture *ending1 = IMG_LoadTexture(renderer,DATADIR "/png/ending1.png");
  SDL_Texture *ending2 = IMG_LoadTexture(renderer,DATADIR "/png/ending2.png");
  SDL_Texture *ending3 = IMG_LoadTexture(renderer,DATADIR "/png/ending3.png");
  SDL_Texture *ending4 = IMG_LoadTexture(renderer,DATADIR "/png/theend.png");

  Mix_Chunk *argh = Mix_LoadWAV(DATADIR "/fx/fx_uaaah.ogg"); // Sound
  Mix_Music *bso = Mix_LoadMUS(DATADIR "/music/ending.ogg"); // Music
  
  SDL_Event keystroke; // Keyboard

  // Variables
  uint8_t step = 0;
  uint16_t fadecounter = 0;
  uint16_t counter = 0;
  uint8_t fullscreench = 0;
  
  // Rects
  SDL_Rect srcending = {0,0,512,448};
  SDL_Rect destending = {0,0,256,224};

  while (*state == 3) {
  
    SDL_RenderClear(renderer);
    
    if (fullscreench == 1) { // Change to fullscreen
      SDL_SetWindowFullscreen(screen, fullscreench ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
      fullscreench = 0;
    }
    
    switch (step) {
      case 0: // ending 1
        SDL_SetTextureAlphaMod(ending1,fadecounter);
        SDL_RenderCopy(renderer,ending1,&srcending,&destending);
        counter ++;
        if (counter == 30)
          Mix_PlayMusic(bso,0);
        if (counter < 85)
          fadecounter += 1;
        if ((counter > 984) && (counter < 1069))
          fadecounter -= 1;
        if (counter == 1069) {
          step = 1;
          fadecounter = 0;
        }
        while (SDL_PollEvent(&keystroke)) {
          if (keystroke.type == SDL_QUIT)
            exit(0);
          if (keystroke.type == SDL_KEYDOWN) {
            if (keystroke.key.keysym.sym == SDLK_ESCAPE)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_q)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_SPACE)
              *state = 0;
            if (keystroke.key.keysym.sym == SDLK_f)
              fullscreench = 1;
          }
        }
      break;
      case 1: // ending 2
        SDL_SetTextureAlphaMod(ending2,fadecounter);
        SDL_RenderCopy(renderer,ending2,&srcending,&destending);
        counter ++;
        if (counter == 1070) // Demon dying
          Mix_PlayChannel(0,argh,0);
        if ((counter > 1069) && (counter < 1153))
          fadecounter += 1;
        if ((counter > 2053) && (counter < 2137))
          fadecounter -= 1;
        if (counter == 2137) {
          step = 2;
          fadecounter = 0;
        }
        while (SDL_PollEvent(&keystroke)) {
          if (keystroke.type == SDL_QUIT)
            exit(0);
          if (keystroke.type == SDL_KEYDOWN) {
            if (keystroke.key.keysym.sym == SDLK_ESCAPE)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_q)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_SPACE)
              *state = 0;
            if (keystroke.key.keysym.sym == SDLK_f)
              fullscreench = 1;
          }
        }
      break;
      case 2: // ending 3
        SDL_SetTextureAlphaMod(ending3,fadecounter);
        SDL_RenderCopy(renderer,ending3,&srcending,&destending);
        counter ++;
        if ((counter > 2137) && (counter < 2221))
          fadecounter += 1;
        if ((counter > 3121) && (counter < 3205))
          fadecounter -= 1;
        if (counter == 3205) {
          step = 3;
          fadecounter = 0;
        }
        while (SDL_PollEvent(&keystroke)) {
          if (keystroke.type == SDL_QUIT)
            exit(0);
          if (keystroke.type == SDL_KEYDOWN) {
            if (keystroke.key.keysym.sym == SDLK_ESCAPE)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_q)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_SPACE)
              *state = 0;
            if (keystroke.key.keysym.sym == SDLK_f)
              fullscreench = 1;
          }
        }
      break;
      case 3: // theend
        // SDL_SetTextureAlphaMod(ending4,fadecounter);
        SDL_RenderCopy(renderer,ending4,&srcending,&destending);
        counter ++;
        if ((counter > 3205) && (counter < 3289))
          fadecounter += 1;
        if (counter == 4189)
          *state = 0;
        while (SDL_PollEvent(&keystroke)) {
          if (keystroke.type == SDL_QUIT)
            exit(0);
          if (keystroke.type == SDL_KEYDOWN) {
            if (keystroke.key.keysym.sym == SDLK_ESCAPE)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_q)
              exit(0);
            if (keystroke.key.keysym.sym == SDLK_SPACE)
              *state = 0;
            if (keystroke.key.keysym.sym == SDLK_f)
              fullscreench = 1;
          }
        }
      break;
      
    }
     
    SDL_RenderPresent(renderer); 

  }

  SDL_DestroyTexture(ending1);
  SDL_DestroyTexture(ending2);
  SDL_DestroyTexture(ending3);
  SDL_DestroyTexture(ending4);
  Mix_FreeChunk(argh);
  Mix_FreeMusic(bso);

}
