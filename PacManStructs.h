// These are in a different file to avoid yet another Arduino IDE bugs:
// http://playground.arduino.cc/Code/Struct#FAQ
//
#ifndef PACMANSTRUCTS_H
#define PACMANSTRUCTS_H

#include <WString.h>

typedef struct
{
  int8_t x, y;
} 
CoordinateStruct;

typedef struct
{
  uint8_t  x;        // X position on SCREEN
  uint8_t  y;        // Y position on SCREEN
  int8_t   tilex;    // X position in tiles
  int8_t   tiley;    // Y position in tiles
  int8_t   tileoffx; // X offset within tile
  int8_t   tileoffy; // Y offset within tile
  uint8_t  dir;      // current direction
  uint8_t  nextDir;  // next desired direction
} 
PositionStruct;

#endif // PacManStructs_h

// End of PacManStructs.h


