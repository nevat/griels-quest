/* loading.c */

#include <SDL_image.h>
#include "loading.h"

void loaddata (uint8_t map[][11][16]) {

  uint8_t i = 0;
  uint8_t j = 0;
  uint k = 0;
  FILE *datafile = fopen(DATADIR "/data/rounds.txt", "r");
  char line[49];
  char temp[3];
  temp[2] = 0;

  /* Load data an put in array */
  fgets (line, 49, datafile);
  for (i=0;i<58;i++) {
    for (j=0;j<11;j++) {
      for (k=0;k<16;k+=1) {
        temp[0] = line[k*3];
        temp[1] = line[k*3 + 1];
        sscanf (temp, "%d", &map[i][j][k]);
      }
      fgets (line, 49, datafile);
    }
    fgets (line, 49, datafile);
  }

  fclose(datafile);

}

void load_music(Mix_Music *bsogame, int round) {

  if(bsogame) {
    Mix_FreeMusic(bsogame);
  }

  switch(round % 5) {
  case 0:
    bsogame = loadmus("stage1");
    break;
  case 1:
    bsogame = loadmus("stage2");
    break;
  case 2:
    bsogame = loadmus("stage3");
    break;
  case 3:
    bsogame = loadmus("stage4");
    break;
  case 4:
    bsogame = loadmus("stage5");
    break;
  }

  Mix_PlayMusic(bsogame, -1); // play looped

}

static char* makepath(const char *folder, const char *file, const char *ext) {
  int len = strlen(DATADIR) + 1; // sep
  len += strlen(folder) + 1; // sep
  len += strlen(file) + 1; // sep
  len += strlen(ext) + 1; // null

  char *result = malloc(len);
  sprintf(result, "%s/%s/%s.%s", DATADIR, folder, file, ext);

  return result;
}

SDL_Texture *loadtexture(const char *file) {
  char *path = makepath("png", file, "png");

  SDL_Texture *result = IMG_LoadTexture(g_state.renderer, path);

  if(!result) fprintf(stderr, "Could not load %s!\n", path);

  free(path);
  return result;
}

Mix_Music *loadmus(const char *file) {
  char *path = makepath("music", file, "ogg");

  Mix_Music *result = Mix_LoadMUS(path);

  if(!result) fprintf(stderr, "Could not load %s!\n", path);

  free(path);
  return result;
}

Mix_Chunk *loadwav(const char *file) {
  char *path = makepath("fx", file, "ogg");

  Mix_Chunk *result = Mix_LoadWAV(path);

  if(!result) fprintf(stderr, "Could not load %s!\n", path);

  free(path);
  return result;
}

bool check_data() {
  const int NUM_CHECKS = 4;

  /* Check every kind of data */
  const char* files[] = {
    DATADIR "/png/startscreen.png",
    DATADIR "/data/rounds.txt",
    DATADIR "/music/history.ogg",
    DATADIR "/fx/fx_hahaha.ogg"
  };

  /* Try to open each file */
  int missing = NUM_CHECKS;
  SDL_RWops *rw;
  for(int i = 0; i < NUM_CHECKS; i++) {
    rw = SDL_RWFromFile(files[i], "rb");
    if (rw) {
      SDL_RWclose(rw);
      missing--;
    }
  }

  /* Everything found */
  if (!missing) return true;

  return false;
}
