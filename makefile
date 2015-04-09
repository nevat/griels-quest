PREFIX?=	/usr

CC?=		gcc
CFLAGS?=	-O2 -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize

CFLAGS+=	`sdl-config --cflags` -DDATADIR="\"$(PREFIX)/share/griels\""
LIBS=		`sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx -lm

PROG=		griels
SRCS=		src/ending.c \
		src/game.c \
		src/hero.c \
		src/history.c \
		src/hud.c \
		src/intro.c \
		src/loading.c \
		src/main.c

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(PROG) $(LIBS)

clean:
	rm -f $(PROG)

# Installation
install:
	cp $(PROG) $(DESTDIR)$(PREFIX)/bin/
	cp griels.desktop $(DESTDIR)$(PREFIX)/share/applications
	mkdir -p $(DESTDIR)$(PREFIX)/share/griels/music
	cp ./music/* $(DESTDIR)$(PREFIX)/share/griels/music
	mkdir -p $(DESTDIR)$(PREFIX)/share/griels/fx
	cp ./fx/* $(DESTDIR)$(PREFIX)/share/griels/fx
	mkdir -p $(DESTDIR)$(PREFIX)/share/griels/data
	cp ./data/* $(DESTDIR)$(PREFIX)/share/griels/data
	mkdir -p $(DESTDIR)$(PREFIX)/share/griels/png
	cp ./png/* $(DESTDIR)$(PREFIX)/share/griels/png
	cp ./png/icon.png $(DESTDIR)$(PREFIX)/share/pixmaps/griels.png

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROG)
	rm $(DESTDIR)$(PREFIX)/share/applications/griels.desktop
	rm $(DESTDIR)$(PREFIX)/share/pixmaps/griels.png
	rm -rf $(DESTDIR)$(PREFIX)/share/griels
