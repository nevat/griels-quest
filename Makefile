PREFIX?=	/usr

CC?=		gcc
CFLAGS?=	-O2 -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize

CFLAGS+=	`sdl2-config --cflags` -DDATADIR="\"$(PREFIX)/share/griels\""
LIBS=		`sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

PROG=		griels
SRCS=		src/ending.c \
		    src/history.c \
		    src/intro.c \
			src/game.c \
			src/hero.c \
			src/hud.c \
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
