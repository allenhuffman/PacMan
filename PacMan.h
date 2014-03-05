#ifndef PACMAN_H
#define PACMAN_H


#define JOYSTICKXPIN 1
#define JOYSTICKYPIN 0

// Used for input/joystick return, and for sprite direction.
// The numbers/order (0-3) must match the entries in the Ghost bitmap!
#define UP         0
#define LEFT       1
#define DOWN       2
#define RIGHT      3
#define DIRS       4

// Maze bitmap
#define MAZEX      0
#define MAZEY      0

// Tile
#define TILEX      1  // Offset to where tiles appear on screen
#define TILEY      1
#define TILEW      28
#define TILEH      31
#define TILESIZE   3  // Each tile is 3x3

#define TILEBYTESPERROW ((TILEW-1)/8+1) // bytes per row in mazeTiles

// Pac-Man
#define PFRATE     0  // Count to 5, display next frame

// Ghosts
#define GHOSTS     4  // Number of ghosts
#define GFRATE     5 // Count to 10, display next frame
// Red, Pink, Blue Orange
#define BLINKY     0  // Red ghost, starts outside of house
#define PINKY      1  // Pink ghost, second out.
#define INKY       2  // Blue ghost, third out.
#define CLYDE      4  // Orange ghost, fourth out.

// Ghost modes
#define HOUSE      0  // Bouncing in the Ghost House
#define CHASE      1
#define SCATTER    2
#define FRIGHTENED 3
#define DEAD       4  // Heading to the ghost house

// Power energizers
#define PELLETRATE 10

#endif

// End of PacMan.h
