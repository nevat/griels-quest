/* ending.c */

#include "ending.h"
#include "main.h"

static void handleControls() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT)
      g_state.scene = GS_EXIT;
    else if (e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          g_state.scene = GS_EXIT;
          break;
        case SDLK_SPACE:
          g_state.scene = GS_INTRO;
          break;
        case SDLK_f:
          toggleFullScreen();
          break;
      }
    }
    else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
      switch(e.cbutton.button) {
        case SDL_CONTROLLER_BUTTON_START:
          g_state.scene = GS_EXIT;
          break;
        case SDL_CONTROLLER_BUTTON_A:
          rumbleController(CR_DECISION);
          g_state.scene = GS_INTRO;
          break;
        case SDL_CONTROLLER_BUTTON_BACK:
          toggleFullScreen();
          break;
      }
    }
  }
}

void ending () {

  // Textures
  SDL_Texture *ending1 = IMG_LoadTexture(g_state.renderer,DATADIR "/png/ending1.png");
  SDL_Texture *ending2 = IMG_LoadTexture(g_state.renderer,DATADIR "/png/ending2.png");
  SDL_Texture *ending3 = IMG_LoadTexture(g_state.renderer,DATADIR "/png/ending3.png");
  SDL_Texture *ending4 = IMG_LoadTexture(g_state.renderer,DATADIR "/png/theend.png");

  Mix_Chunk *argh = Mix_LoadWAV(DATADIR "/fx/fx_uaaah.ogg"); // Sound
  Mix_Music *bso = Mix_LoadMUS(DATADIR "/music/ending.ogg"); // Music

  // Variables
  uint8_t step = 0;
  uint16_t fadecounter = 0;
  uint16_t counter = 0;
  
  // Rects
  SDL_Rect srcending = {0,0,512,448};
  SDL_Rect destending = {0,0,256,224};

  while (g_state.scene == GS_ENDING) {
    SDL_RenderClear(g_state.renderer);
    handleControls();

    switch (step) {
      case 0: // ending 1
        SDL_SetTextureAlphaMod(ending1,fadecounter);
        SDL_RenderCopy(g_state.renderer,ending1,&srcending,&destending);
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
      break;
      case 1: // ending 2
        SDL_SetTextureAlphaMod(ending2,fadecounter);
        SDL_RenderCopy(g_state.renderer,ending2,&srcending,&destending);
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
      break;
      case 2: // ending 3
        SDL_SetTextureAlphaMod(ending3,fadecounter);
        SDL_RenderCopy(g_state.renderer,ending3,&srcending,&destending);
        counter ++;
        if ((counter > 2137) && (counter < 2221))
          fadecounter += 1;
        if ((counter > 3121) && (counter < 3205))
          fadecounter -= 1;
        if (counter == 3205) {
          step = 3;
          fadecounter = 0;
        }
      break;
      case 3: // theend
        // SDL_SetTextureAlphaMod(ending4,fadecounter);
        SDL_RenderCopy(g_state.renderer,ending4,&srcending,&destending);
        counter ++;
        if ((counter > 3205) && (counter < 3289))
          fadecounter += 1;
        if (counter == 4189)
          g_state.scene = GS_INTRO;
      break;
      
    }
     
    SDL_RenderPresent(g_state.renderer);

  }

  SDL_DestroyTexture(ending1);
  SDL_DestroyTexture(ending2);
  SDL_DestroyTexture(ending3);
  SDL_DestroyTexture(ending4);
  Mix_FreeChunk(argh);
  Mix_FreeMusic(bso);

}
