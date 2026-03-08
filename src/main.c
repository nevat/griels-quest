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

int main(int argc, char* argv[]) {
  // set defaults
  g_state.renderer = NULL;
  g_state.scene = GS_INTRO;
  g_state.level = 1;
  window = NULL;
  fullscreen = false;

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

  // Init joystick
  SDL_Joystick *joystick = NULL;
  if (SDL_Init(SDL_INIT_JOYSTICK) >= 0) {
    joystick = SDL_NumJoysticks() > 0 ? SDL_JoystickOpen(0) : NULL;
    SDL_JoystickEventState(SDL_ENABLE);
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
  SDL_JoystickClose(joystick);
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
