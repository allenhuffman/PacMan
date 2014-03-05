#include <avr/pgmspace.h>
#ifndef GHOSTBITMAP_H
#define GHOSTBITMAP_H

#define GHOSTW     5  // Width of ghost
#define GHOSTH     5  // Height of ghost
#define GDIRS      4  // Ghost directions
#define GFRAMES    2  // Frames for the ghost

extern const unsigned char ghostBitmap[GDIRS][GFRAMES][GHOSTH+2];
#endif

// End of GhostBitmap.h
