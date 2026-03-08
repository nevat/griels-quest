// Griel's Quest for the Sangraal
// Started on 17/04/2013
// Started to migrate to SDL2 in 27/06/2025 (omg!)
// Under GPL v3 license

#include "main.h"
#include "intro.h"
#include "history.h"
#include "game.h"
#include "ending.h"

// globals
state_s g_state;

// locals
static SDL_Window *window;
static bool fullscreen;
static SDL_GameController *controller;

int main(int argc, char* argv[]) {
  // set defaults
  g_state.renderer = NULL;
  g_state.scene = GS_INTRO;
  g_state.level = 1;
  window = NULL;
  fullscreen = false;
  controller = NULL;

  // handle parameters
  for (int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-f") == 0)
      fullscreen = true;
    if(strcmp(argv[i], "-w") == 0)
      fullscreen = false;
#if DEBUG
    // allow jumping scenes
    if(strcmp(argv[i], "-h") == 0)
      g_state.scene = GS_HISTORY;
    if(strcmp(argv[i], "-g") == 0)
      g_state.scene = GS_GAME;
    if(strcmp(argv[i], "-e") == 0)
      g_state.scene = GS_ENDING;
#endif
  }

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // Init SDL2

  int winflags = SDL_WINDOW_RESIZABLE;
  if(fullscreen)
    winflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  window = SDL_CreateWindow("Griel's Quest for the Sangraal v1.0",
    SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_W*2,SCREEN_H*2,
    winflags); // Creating window

  // Create renderer
  g_state.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  SDL_RenderSetLogicalSize(g_state.renderer,SCREEN_W,SCREEN_H);

  // Init audio
  Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,1,4096);
  Mix_AllocateChannels(3);

  // Init Game Controller
  if (SDL_Init(SDL_INIT_GAMECONTROLLER) == 0) {
    int nSticks = SDL_NumJoysticks();
    for (int i = 0; i < nSticks; i++) {
      if (SDL_IsGameController(i)) {
        // open first one
        controller = SDL_GameControllerOpen(i);
        break;
      }
    }

    SDL_GameControllerEventState(SDL_ENABLE);
  }

  SDL_ShowCursor(SDL_DISABLE); // Disable mouse

  // Loading part of the game
  while (g_state.scene < GS_EXIT) {
    switch (g_state.scene) {
      case GS_INTRO:
        game_intro ();
        break;
      case GS_HISTORY:
        history ();
        break;
      case GS_GAME:
        game ();
        break;
      case GS_ENDING:
        ending ();
        break;
    }
  }

  // Cleaning
  if(controller)
    SDL_GameControllerClose(controller);
  SDL_DestroyRenderer(g_state.renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0; // Exit

}

void toggleFullScreen() {
  fullscreen = !fullscreen;

  SDL_SetWindowFullscreen(window,
    fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void rumbleController(ControllerRumble type) {
  if(!controller) return;

  int low, high, duration;

  switch(type) {
    case CR_DECISION:
      low = 900;
      high = 600;
      duration = 200;
      break;
    case CR_POW:
      low = 1200;
      high = 2000;
      duration = 400;
      break;
    case CR_DEATH:
      low = 1000;
      high = 5000;
      duration = 700;
      break;
    case CR_GRAIL:
      low = 10000;
      high = 20000;
      duration = 1000;
      break;
  }

  SDL_GameControllerRumble(controller, low, high, duration);
}
