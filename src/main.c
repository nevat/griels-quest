// Griel's Quest for the Sangraal
// Started on 17/04/2013
// Started to migrate to SDL2 in 27/06/2025 (omg!)
// Under GPL v3 license

# include "main.h"

SDL_Renderer *renderer;

int main() {

  // SDL_Surface *screen = NULL;
  uint8_t state = 0;
  uint8_t level = 0;
  uint8_t fullscreen = 0;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // Init SDL2

  SDL_Window *screen = SDL_CreateWindow("Griel's Quest for the Sangraal",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,512,448,fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_RESIZABLE); // Creating window

  // Create renderer
  renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  SDL_RenderSetLogicalSize(renderer,256,224);

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
  // system("xset r off"); // Disable repeat keys

  // Loading part of the game
  while (state < 4) {
    switch (state) {
      case 0: game_intro (screen, &state, &level);
	          break;
      case 1: history (screen, &state);
              break;
      case 2: game (screen, &state, &level);
              break;
      case 3: ending (screen,&state);
              break;
    }
  }

  // Cleaning
  SDL_JoystickClose(joystick);
  // SDL_DestroyTexture(target);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();

  return 0; // Exit

}
