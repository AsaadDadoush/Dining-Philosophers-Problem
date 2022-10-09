/******************************************************************************
 *  DiningTable.h
 *
 *  Generates a dining table with n persons, n rice bowls and n chopsticks
 *  around it. This header and the accompanying DiningTable.o file are needed
 *  to show graphically your solution to the classical Dining Philosophers problem.
 *
 *  Assume that your solution is in a file called "DP.c" then:
 *
 *  Compilation:
 *    in Linux using gcc and SDL2:
 *       gcc DP.c -c -o DP.o
 *       gcc DiningTable.o DP.o -o dp -lSDL_bgi -lSDL2 -lpthread -lm
 *
 *  Execution:
 *       dp n
 *
 *  Dependencies: graphics.h, DiningTable.o, and this file
 *  needs: - Some desktop GUI environment for graphics
 *         - SDL2 Library: libsdl2-2.0
 *         - SDL2 development package: libsdl2-dev
 *         - SDL_bgi 2D graphics Package: sdl_bgi_2.5.0-1
 *
 *
 *  Author Dr. Abdulghani M. Al-Qasimi
 *  Version 2.01 2021/10/26
 *
 ******************************************************************************/
#define MAXRAND RAND_MAX                // Limit the maximum random number.

int size;                               // Dimension of the table (no. chairs)

// initializes the graphics syatem
// must be called in the beginning
// parameter num is used to draw
// a table, num philosophers and
// num chopsticks on the table 
void init(int num);

// chages person i's state to hungry
void hungry(int i);

// chages person i's state to eating
void eat(int i);

// chages person i's state to thinking
void think(int i);

// changes state of chopstick i to taken
// with gravity to the left when g = 'l'
// or gravity to the right when g = 'r'
void takeChopstick(int i, char g);

// changes state of chopstick i to available
void putChopstick(int i);

// clean up and finish
// must be called before exiting
void finish();
