/* loading.c */

# include "loading.h"

void loaddata (int map[][11][16]) {

	uint i = 0;
	uint j = 0;
	uint k = 0;
	FILE *datafile = fopen("/usr/share/griels/data/rounds.txt", "r");
	char line[49];
	char temp[2];;

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

	if ((round == 0) || (round == 5) || (round == 10) || (round == 15) || (round == 20) || (round == 25) || (round == 30) || (round == 35) || (round == 40) || (round == 45) || (round == 50) || (round == 55))
		bsogame = Mix_LoadMUS("/usr/share/griels/music/stage1.ogg");
	if ((round == 1) || (round == 6) || (round == 11) || (round == 16) || (round == 21) || (round == 26) || (round == 31) || (round == 36) || (round == 41) || (round == 46) || (round == 51) || (round == 56))
		bsogame = Mix_LoadMUS("/usr/share/griels/music/stage2.ogg");
	if ((round == 2) || (round == 7) || (round == 12) || (round == 17) || (round == 22) || (round == 27) || (round == 32) || (round == 37) || (round == 42) || (round == 47) || (round == 52) || (round == 57))
		bsogame = Mix_LoadMUS("/usr/share/griels/music/stage3.ogg");
	if ((round == 3) || (round == 8) || (round == 13) || (round == 18) || (round == 23) || (round == 28) || (round == 33) || (round == 38) || (round == 43) || (round == 48) || (round == 53))
		bsogame = Mix_LoadMUS("/usr/share/griels/music/stage4.ogg");
	if ((round == 4) || (round == 9) || (round == 14) || (round == 19) || (round == 24) || (round == 29) || (round == 34) || (round == 39) || (round == 44) || (round == 49) || (round == 54))
		bsogame = Mix_LoadMUS("/usr/share/griels/music/stage5.ogg");

	Mix_PlayMusic(bsogame, -1);

}