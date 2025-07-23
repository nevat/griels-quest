# Griel's Quest for the Sangraal

## ABOUT THIS GAME

"Griel's Quest for the Sangraal" is a game released for MSX2 systems in the
year 1990 (only on Japan). In 2005 was ported to MSX1 systems by Karoshi Corp.

This version is a port of MSX1 version of the game to the GNU/Linux systems.
Featuring all the levels, objects and enemies. The program is written in
C language with the help of SDL2 libraries.

## KEYS

- Use the arrows of keyboard to move Griel.
- <kbd>F</kbd> key switch between fullscreen/windowed mode.
- <kbd>Q</kbd> key exits the program.
- <kbd>ESC</kbd> key will restart the current game (losing a life).

## INSTALLATION FROM SOURCE

To compile the program you need GCC compiler and SDL libraries.

In Fedora systems you can install all of this packages with this command:

    # dnf install gcc make SDL2_mixer-devel SDL2_image-devel

For Ubuntu/Debian users, run this:

    $ sudo apt-get install gcc libsdl2-mixer-dev libsdl2-image-dev


Unpack the source code file:

    $ tar vxfz griels-quest.tar.gz

Enter the directory created an run:

    $ make

As root, install the game with:

    # make install # (Ubuntu users run: $ sudo make install)

A icon will appear in your application menu, in game section.
Alternatively you can run the game with the order "griels".

## UNINSTALLATION FROM SOURCE

Enter the directory and run (as root):

    # make uninstall # (Ubuntu users run: $ sudo make uninstall).

## LICENSE

The code is licensed under the GNU GPL version 3, see COPYING file for
reference. Anyone can download, see, change and redistribute the code.
