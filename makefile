all: griel

griel: ./src/main.c ./src/history.c ./src/intro.c ./src/game.c ./src/hud.c ./src/hero.c ./src/loading.c ./src/ending.c
	gcc -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize ./src/main.c src/history.c ./src/intro.c ./src/game.c ./src/hud.c ./src/hero.c ./src/loading.c ./src/ending.c -o griels `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm

clean:
	rm -f griels

# Installation
install:
	cp griels /usr/bin/
	cp griels.desktop /usr/share/applications
	mkdir -p /usr/share/griels/music
	cp ./music/* /usr/share/griels/music
	mkdir -p /usr/share/griels/fx
	cp ./fx/* /usr/share/griels/fx
	mkdir -p /usr/share/griels/data
	cp ./data/* /usr/share/griels/data
	mkdir -p /usr/share/griels/png
	cp ./png/* /usr/share/griels/png
	cp ./png/icon.png /usr/share/pixmaps/griels.png

uninstall:
	rm /usr/bin/griels
	rm /usr/share/applications/griels.desktop
	rm /usr/share/pixmaps/griels.png
	rm -rf /usr/share/griels
