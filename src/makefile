all: griel

griel: main.c history.c intro.c game.c
	gcc -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize main.c history.c intro.c game.c hud.c hero.c loading.c -o griel `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm

clean:
	rm -f griel
