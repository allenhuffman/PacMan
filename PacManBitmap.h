#include <avr/pgmspace.h>
#ifndef PACMANBITMAP_H
#define PACMANBITMAP_H

#define PLAYERW    5  // Width of player
#define PLAYERH    5  // Height of player
#define PDIRS      4  // Player directions
#define PFRAMES    4  // Frames for the player

extern const unsigned char pacmanBitmap[PDIRS][PFRAMES][PLAYERH+2];
#endif

// End of PacManBitmap.h
