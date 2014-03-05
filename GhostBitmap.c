#include "GhostBitmap.h"

// Ghosts
// Bitmaps must be in the order 0-UP, 1-LEFT, 2-DOWN, 3-RIGHT
PROGMEM const unsigned char ghostBitmap[GDIRS][GFRAMES][GHOSTH+2] = {
  { // Up
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b10101000,
      0b11111000,
      0b11111000,
      0b10101000
    }
    ,
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b10101000,
      0b11111000,
      0b11111000,
      0b01010000
    }
  }
  ,
  { // Left
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b01011000,
      0b11111000,
      0b10101000
    }
    ,
    {
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b01011000,
      0b11111000,
      0b01010000
    }
  }
  ,
  { // Down
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b10101000,
      0b11111000,
      0b10101000
    }
    ,
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b10101000,
      0b11111000,
      0b01010000
    }
  }
  ,
  { // Right
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11010000,
      0b11111000,
      0b10101000
    }
    ,
    { 
      GHOSTW,GHOSTH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11010000,
      0b11111000,
      0b01010000
    }
  }
};

// End of GhostBitmap.c

