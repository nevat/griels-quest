/* loading.c */

# include "loading.h"

void loaddata (int map[][11][16]) {

	uint i = 0;
	uint j = 0;
	uint k = 0;
	FILE *datafile = fopen("../data/rounds.txt", "r");
	char line[49];
	char temp[2];;

	/* Load data an put in array */
	fgets (line, 49, datafile);
	for (i=0;i<10;i++) {
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

	if ((round == 0) || (round == 5) || (round == 10))
		bsogame = Mix_LoadMUS("../music/stage1.ogg");
	if ((round == 1) || (round == 6))
		bsogame = Mix_LoadMUS("../music/stage2.ogg");
	if ((round == 2) || (round == 7))
		bsogame = Mix_LoadMUS("../music/stage3.ogg");
	if ((round == 3) || (round == 8))
		bsogame = Mix_LoadMUS("../music/stage4.ogg");
	if ((round == 4) || (round == 9))
		bsogame = Mix_LoadMUS("../music/stage5.ogg");

	Mix_PlayMusic(bsogame, -1);

}