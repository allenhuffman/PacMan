#include "PacManBitmap.h"

// Pac-Man bitmaps.
// Bitmaps must be in the order 0-UP, 1-LEFT, 2-DOWN, 3-RIGHT
PROGMEM const unsigned char pacmanBitmap[PDIRS][PFRAMES][PLAYERH+2] = {
  { // Up
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      0b01010000,
      0b11011000,
      0b11111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b00000000,
      0b10001000,
      0b11011000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01010000,
      0b11011000,
      0b11111000,
      0b11111000,
      0b01110000
    }
  }
  ,
  { // Left
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      0b01110000,
      0b11111000,
      0b00111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b00111000,
      0b00011000,
      0b00111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b00111000,
      0b11111000,
      0b01110000
    }
  }
  ,  
  { // Down
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      0b01110000,
      0b11111000,
      0b11111000,
      0b11011000,
      0b01010000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11011000,
      0b10001000,
      0b00000000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11111000,
      0b11011000,
      0b01010000
    }
  }
  ,
  { // Right
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11111000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11000000,
      0b11111000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11100000,
      0b11000000,
      0b11100000,
      0b01110000
    }
    ,
    { 
      PLAYERW,PLAYERH,  // width, height
      //12345---
      0b01110000,
      0b11111000,
      0b11000000,
      0b11111000,
      0b01110000
    }
  }
};

// End of PacManBitmap.c

