// To work around an Arduino IDE bug, we have to include this first. Bad.
#include "PacManStructs.h"

#define nop() __asm volatile ("nop")
#if 1
nop();
#endif

/*-----------------------------------------------------------------------------
 
 Arduino Pac-Man for TVout
 By Allen C. Huffman
 www.subethasoftware.com
 
 An attempt to recreate the classic 1980s game.
 
 2014-02-08 0.0 allenh - Accidental beginning.
 2014-02-15 0.0 allenh - Recreated using tile x/y mechanism for wall detection.
 2014-02-16 0.0 allenh - Ghost movement testing.
 2014-02-17 0.0 allenh - Ghost targeting.
 2014-03-04 0.0 allenh - Splitting up in to multiple files.
 
 TODO:
 1. Make the game work.
 2. Handle dots so ghosts can pass over them (detect, redraw) and Pac-Man can
    eat them (detect, score, don't redraw).
 3. Fruits.
 4. Intermission scenes, high score, title screen, etc.
 -----------------------------------------------------------------------------*/
#define VERSION "0.0"

#include <TVout.h>

#include "PacMan.h"
#include "MazeBitmap.h"
#include "PacManBitmap.h"
#include "GhostBitmap.h"
#include "MiscBitmap.h"

/*---------------------------------------------------------------------------*/

// The game is based on a set of tiles that make up the screen. This
// data represents the maze, with each bit in the byte indicating a wall (1)
// or a path (0). This is used to determine where the walls are (so the
// characters can't run through them).

PROGMEM const unsigned char mazeTiles[TILEH][TILEBYTESPERROW] = {
  0b11111111, 0b11111111, 0b11111111, 0b11110000,
  0b10000000, 0b00000110, 0b00000000, 0b00010000,
  0b10111101, 0b11110110, 0b11111011, 0b11010000,
  0b10111101, 0b11110110, 0b11111011, 0b11010000,
  0b10111101, 0b11110110, 0b11111011, 0b11010000,
  0b10000000, 0b00000000, 0b00000000, 0b00010000,
  0b10111101, 0b10111111, 0b11011011, 0b11010000,
  0b10111101, 0b10111111, 0b11011011, 0b11010000,
  0b10000001, 0b10000110, 0b00011000, 0b00010000,
  0b11111101, 0b11110110, 0b11111011, 0b11110000,
  0b00000101, 0b11110110, 0b11111010, 0b00000000,
  0b00000101, 0b10000000, 0b00011010, 0b00000000,
  0b00000101, 0b10111111, 0b11011010, 0b00000000, // Ghost house top
  //  0b00000101, 0b10111100 , 0b11011010, 0b00000000, // Ghost house top
  0b11111101, 0b10100000, 0b01011011, 0b11110000,
  //0b10000000, 0b00100000, 0b01000000, 0b00010000, // Tunnels
  0b10000100, 0b00100000, 0b01000000, 0b10010000, // Tunnels
  0b11111101, 0b10100000, 0b01011011, 0b11110000,
  0b00000101, 0b10111111, 0b11011010, 0b00000000,
  0b00000101, 0b10000000, 0b00011010, 0b00000000,
  0b00000101, 0b10111111, 0b11011010, 0b00000000,
  0b11111101, 0b10111111, 0b11011011, 0b11110000,
  0b10000000, 0b00000110, 0b00000000, 0b00010000,
  0b10111101, 0b11110110, 0b11111011, 0b11010000,
  0b10111101, 0b11110110, 0b11111011, 0b11010000,
  0b10001100, 0b00000000, 0b00000011, 0b00010000,
  0b11101101, 0b10111111, 0b11011011, 0b01110000,
  0b11101101, 0b10111111, 0b11011011, 0b01110000,
  0b10000001, 0b10000110, 0b00011000, 0b00010000,
  0b10111111, 0b11110110, 0b11111111, 0b11010000,
  0b10111111, 0b11110110, 0b11111111, 0b11010000,
  0b10000000, 0b00000000, 0b00000000, 0b00010000,
  0b11111111, 0b11111111, 0b11111111, 0b11110000
};

/*---------------------------------------------------------------------------*/

// Ghost SCATTER mode targets. Each coordinate represents the tile a ghost is
// trying to reach when in scatter mode.
//
// Since the tile grid we are using is not the full arcade size, the target
// tiles are actually off the visible screen. That is why there are some
// negative numbers here. :) It all works out in the math, later.

PROGMEM const CoordinateStruct scatterTarget[GHOSTS] =
{
  (TILEW-1)-2,-4,     // 0-RED, top right
  2,          -4,     // 1-PINK, top left
  (TILEW-1),  TILEH,  // 3-BLUE, bottom right
  0,          TILEH,  // 2-ORANGE, bottom left
};

// To check the tile in front of Pac-Man, we will use this table to figure
// out which tile that is.
// Entries must be in the order 0-UP, 1-LEFT, 2-DOWN, 3-RIGHT
PROGMEM const CoordinateStruct nextTileOffset[DIRS] =
{
  0, -1,  // 0-UP
  -1, 0,  // 1-LEFT
  0,  1,  // 2-DOWN
  1,  0   // 3-RIGHT
};

/*---------------------------------------------------------------------------*/

TVout TV;

void setup()
{
  Serial.begin(9600);

  TV.begin(NTSC, 120, 96);

  TV.clear_screen();

  drawMaze();
  //drawTileGrid();
  //drawWallTiles();
  //drawTileCenters();
}

void loop()
{
  int8_t nextX, nextY;

  // Sprites
  PositionStruct  pac, ghost[GHOSTS];

  uint8_t pacFrame; // Player frame to display
  uint8_t pacRate;  // Frame speed counter
  uint8_t pacSpeed;
  uint8_t pacSpeedCounter;

  uint8_t ghostFrame;
  uint8_t ghostRate;
  uint8_t ghostSpeed;
  uint8_t ghostSpeedCounter;
  uint8_t ghostMode[GHOSTS];

  uint8_t energizerRate;
  uint8_t energizerState;

  uint8_t  i;

  /*-------------------------------------------------------------------------*/
  // Set initial tile and offset where Pac-Man will start.  
  pac.tilex = 14;
  pac.tileoffx = -1;
  pac.tiley = 23;
  pac.tileoffy = 0;
  pac.x = tileToScreen(pac.tilex, pac.tileoffx);
  pac.y = tileToScreen(pac.tiley, pac.tileoffy);
  pac.dir = LEFT;
  pac.nextDir = LEFT; // FIXTHIS later

  pacFrame = 0;
  pacRate = 0;
  pacSpeed = 2;
  pacSpeedCounter = 0;

  // Initialize ghosts.
  ghost[0].tilex = 14;
  ghost[0].tileoffx  = -1;
  ghost[0].tiley = 11;
  ghost[0].tileoffy  = 0;

  ghost[1].tilex = 12;
  ghost[1].tileoffx  = -1;
  ghost[1].tiley = 14;
  ghost[1].tileoffy = 0;

  ghost[2].tilex = 14;
  ghost[2].tileoffx = -1;
  ghost[2].tiley = 14;
  ghost[2].tileoffy = 0;

  ghost[3].tilex = 16;
  ghost[3].tileoffx = -1;
  ghost[3].tiley = 14;
  ghost[3].tileoffy = 0;

  //-----------------------------------------
  // FIXTHIS -- DEBUG TESTING!!!
  for (uint8_t i=1; i<GHOSTS; i++)
  {
    ghost[i].tilex = ghost[0].tilex;
    ghost[i].tiley = ghost[0].tiley;
    ghost[i].tileoffx = ghost[0].tileoffx;
    ghost[i].tileoffy = ghost[0].tileoffy;
    ghost[i].dir = LEFT;
    ghost[i].nextDir = LEFT;
    ghostMode[i] = SCATTER;
  }//----------------------------------------

  // Initialize ghosts, part 2.
  for (uint8_t i=0; i<GHOSTS; i++)
  {
    ghost[i].x = tileToScreen(ghost[i].tilex, ghost[i].tileoffx);
    ghost[i].y = tileToScreen(ghost[i].tiley, ghost[i].tileoffy);

    ghostMode[i] = HOUSE;
  }

  ghostMode[0] = SCATTER; // This one actually starts outside the house.

  ghost[0].dir = LEFT;
  ghost[1].dir = UP;
  ghost[2].dir = DOWN;
  ghost[3].dir = UP;

  // DEBUG!
  ghost[0].dir = RIGHT;
  ghostMode[1] = SCATTER;
  ghost[1].dir = LEFT;
  ghostMode[2] = SCATTER;
  ghost[2].dir = RIGHT;
  ghostMode[3] = SCATTER;
  ghost[3].dir = LEFT;

  ghostFrame = 0;
  ghostRate = 0;
  ghostSpeed = 2;
  ghostSpeedCounter = 0;

  /*-------------------------------------------------------------------------*/

  TV.delay_frame(30);

  while(1)
  {
    uint8_t dir;

    // Set Pac-Man's desired direction.
    dir = readJoystick();
    if (dir<DIRS)
    {
      pac.nextDir = dir;
    }
    else
    {
      pac.nextDir = pac.dir;
    }

    // Wait for end of frame display.
    TV.delay_frame(1);

    // Erase player.
    TV.draw_rect(pac.x-2, pac.y-2, 4, 4, BLACK, BLACK);

    // Erase ghosts.
    for (uint8_t i=0; i<GHOSTS; i++)
    {
      TV.draw_rect(ghost[i].x-2, ghost[i].y-2, 4, 4, BLACK, BLACK);
    }

    // Move Pac-Man.
    pacSpeedCounter++;
    if (pacSpeedCounter>pacSpeed)
    {
      pacSpeedCounter = 0;

      // Move Pac-Man
      if (moveTile(&pac)==true)
      {
        // Animate Pac-Man frame.
        pacRate++;
        if (pacRate>=PFRATE)
        {
          pacRate = 0;
          pacFrame++;
          if (pacFrame>=PFRAMES)
          {
            pacFrame=0;
          }
        }
      }
    }

    // Move ghosts.
    ghostSpeedCounter++;
    if (ghostSpeedCounter>ghostSpeed)
    {
      ghostSpeedCounter = 0;

      for (i=0; i<GHOSTS; i++)
      {
        // Move a ghost.
        moveTile(&ghost[i]);

        // What is next? We check every time we reach the center of a tile.
        if (ghost[i].tileoffx==0 && ghost[i].tileoffy==0)
        {
          // Skip ghosts in the ghost house
          if (ghostMode[i]==HOUSE) continue;

          // Get the next tile in the direction the character is facing.
          if (getNextTile(ghost[i].tilex, ghost[i].tiley, ghost[i].dir,
          &nextX, &nextY)==true)
          {
            uint8_t dir;
            int8_t  potentialX, potentialY;
            uint8_t reverseDir;
            uint8_t shortestDist;
            uint8_t shortestDir;
            uint8_t tempDist;

            reverseDir = getReverseDir(ghost[i].dir);
            shortestDist = 255;

            // Check each direction from next tile.
            for (dir=0; dir<DIRS; dir++)
            {
              // Skip backwards, since we can't go that way.
              if (dir==reverseDir)
              {
                continue;
              }

              // Check tile in that directions.
              // There are four spots where ghosts are not allowed to
              // go up, so if dir is up, and it's those spots, skip.
              if (dir==UP)
              {
                if ((nextY==11 || nextY==23) && (nextX==12 || nextX==15))
                {
                  continue;
                }
              }

              // Get the tiles around the next tile to check their distance.
              getNextTile(nextX, nextY, dir, &potentialX, &potentialY);

              // Skip walls, since we can't go that way.
              if (getTileStatus(potentialX, potentialY)!=0)
              {
                continue;
              }

              // HACK! This is here to force BLINKY to target Pac-Man like
              // he would during the normal game.
              if (i==BLINKY)
              {
                tempDist = getTileDistance(potentialX, potentialY,
                pac.tilex, pac.tiley);
              }
              else
              {
                // If here, check the distance to the target.
                tempDist = getTileDistance(potentialX, potentialY,
                pgm_read_byte_near(&scatterTarget[i].x),
                pgm_read_byte_near(&scatterTarget[i].y));
              }

              if (tempDist < shortestDist)
              {
                shortestDist = tempDist;
                shortestDir = dir;
              }
            } // end of for (dir=0; dir<DIRS; dir++)

            // If here, we know which way to go.
            ghost[i].nextDir = shortestDir;

          } // end of getNextTile()
        } // end of if (ghost[i].tileoffx==0 && ghost[i].tileoffy==0)
      } // enf of for (i=0; i<GHOSTS; i++)
    }
    /*-----------------------------------------------------------------------*/

    // Draw Pac-Man
    TV.bitmap(pac.x-2, pac.y-2, pacmanBitmap[pac.dir][pacFrame]);

    // Draw ghosts.
    for (uint8_t i=0; i<GHOSTS; i++)
    {
      // nextDir, so it looks where it is about to turn.
      TV.bitmap(ghost[i].x-2, ghost[i].y-2, ghostBitmap[ghost[i].nextDir][ghostFrame]);
    }

    /*-----------------------------------------------------------------------*/

    // Animate ghosts.
    ghostRate++;
    if (ghostRate>=GFRATE)
    {
      ghostRate = 0;
      ghostFrame++;
      if (ghostFrame>=GFRAMES)
      {
        ghostFrame=0;
      }
    }

    // Animate (blink) energizers.
    energizerRate++;
    if (energizerRate>PELLETRATE)
    {
      energizerRate = 0;
      energizerState = (energizerState==0);
      if (energizerState==1)
      {
        // Draw power energizers
        TV.bitmap(3, 10, energizerBitmap);
        TV.bitmap(78, 10, energizerBitmap);
        TV.bitmap(3, 70, energizerBitmap);
        TV.bitmap(78, 70, energizerBitmap);
      }
      else
      {
        TV.draw_rect(3, 10, PELLETW-1, PELLETH-1, BLACK, BLACK);
        TV.draw_rect(78, 10, PELLETW-1, PELLETH-1, BLACK, BLACK);
        TV.draw_rect(3, 70, PELLETW-1, PELLETH-1, BLACK, BLACK);
        TV.draw_rect(78, 70, PELLETW-1, PELLETH-1, BLACK, BLACK);
      }
    } 
  }
}

/*---------------------------------------------------------------------------*/

void drawMaze()
{
  TV.bitmap(MAZEX, MAZEY, mazeBitmap);
}

/*---------------------------------------------------------------------------*/

uint8_t getReverseDir(uint8_t dir)
{
  switch(dir)
  {
  case LEFT:
    return RIGHT;
  case RIGHT:
    return LEFT;
  case UP:
    return DOWN;
  case DOWN:
    return UP;
  default:
    return dir;
  }
}

/*---------------------------------------------------------------------------*/

// Given tile x/y, return whether that tile is path (0) or wall (1)
uint8_t getTileStatus(int8_t tilex, int8_t tiley)
{
  uint8_t byte = pgm_read_byte_near(&mazeTiles[tiley][tilex/8]);
  uint8_t bit = tilex-((tilex/8)*8);
  return bitRead(byte, 7-bit);
}

/*---------------------------------------------------------------------------*/

// Return the distance between two coordinates. Math is hard.
uint8_t getTileDistance(int8_t x, int8_t y, int8_t targetx, int8_t targety)
{
  int8_t distx, disty;
  distx = targetx-x;
  disty = targety-y;
  //return sqrt( (distx*distx)+(disty*disty));

  return abs(distx)+abs(disty);
}

/*---------------------------------------------------------------------------*/

bool getNextTile(int8_t x, int8_t y, uint8_t dir, int8_t *nextX,
int8_t *nextY)
{
  if (dir >= DIRS) return false;

  *nextX = x + pgm_read_byte_near(&nextTileOffset[dir].x);
  *nextY = y + pgm_read_byte_near(&nextTileOffset[dir].y);

  return true;
}

/*---------------------------------------------------------------------------*/

bool moveTile(PositionStruct *pos)
{
  int8_t mx, my;

  mx = 0;
  my = 0;

  switch (pos->dir)
  {
  case UP:
    my = -1;
    break;
  case LEFT:
    mx = -1;
    break;
  case DOWN:
    my = 1;
    break;
  case RIGHT:
    mx = 1;
    break;
  default:
    break;
  }

  // Are we at the center of a tile?
  if (pos->tileoffx==0 && mx!=0) // Moving on X axis (LEFT/RIGHT)?
  {
    // Is there a wall there?
    if (getTileStatus(pos->tilex + mx, pos->tiley)!=0)
    {
      // Yes, so stop X axis movement.
      mx = 0;
    }
  }

  if (pos->tileoffy==0 && my!=0) // Moving on Y axis (UP/DOWN)?
  {
    // Is there a wall there?
    if (getTileStatus(pos->tilex, pos->tiley + my)!=0)
    {
      // Yes, so stop Y axis movement.
      my = 0;
    }
  }

  pos->x = pos->x + mx;
  pos->tileoffx = pos->tileoffx + mx;
  if (pos->tileoffx < -1)
  {
    pos->tileoffx = 1;
    (pos->tilex)--;
  }
  else if (pos->tileoffx > 1)
  {
    pos->tileoffx = -1;
    (pos->tilex)++;
  }

  pos->y = pos->y + my;
  pos->tileoffy = pos->tileoffy + my;
  if (pos->tileoffy < -1)
  {
    pos->tileoffy = 1;
    (pos->tiley)--;
  }
  else if (pos->tileoffy > 1)
  {
    pos->tileoffy = -1;
    (pos->tiley)++;
  }

  // At every intersection, check to see if we need to change direction.
  // Do we want to go somewhere else?
  if (pos->nextDir!=pos->dir)
  {
    if (pos->tileoffx==0 && pos->tileoffy==0)
    {
      int8_t nextX, nextY;

      if (getNextTile(pos->tilex, pos->tiley, pos->nextDir, &nextX, &nextY)==true)
      {
        if (getTileStatus(nextX, nextY)==0)
        {
          pos->dir = pos->nextDir;
        }
      }
    }
  }

  // Let user know if we moved.
  if (mx==0 && my==0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

/*---------------------------------------------------------------------------*/

// Tile + Tile Offset to screen pixel
int8_t tileToScreen(int8_t tile, int8_t offset)
{
  return TILEX+(tile*TILESIZE)+1+offset;
}

/*---------------------------------------------------------------------------*/

// Some utility functions to do things with the tile map.

// Draw tiles for the walls.
void drawWallTiles()
{
  // Draw grid center dots.
  for (int8_t tilex=0; tilex<TILEW; tilex++)
  {
    for (int8_t tiley=0; tiley<TILEH; tiley++)
    {
      if (getTileStatus(tilex, tiley)!=0)
      {
        TV.draw_rect(TILEX+(tilex*3), TILEY+(tiley*3), 2, 2, WHITE, WHITE);
      }
    }
  }
}

// Draw tile center dots.
void drawTileCenters()
{
  for (int8_t tilex=0; tilex<TILEW; tilex++)
  {
    for (int8_t tiley=0; tiley<TILEH; tiley++)
    {
      if (getTileStatus(tilex, tiley)!=0)
      {
        TV.set_pixel(TILEX+(tilex*3)+1, TILEY+(tiley*3)+1, WHITE);
      }
    }
  }
}

// Draw tile grid.
void drawTileGrid()
{
  for (int8_t x=0; x<TILEW; x++)
  {
    for (int8_t y=(x & 1); y<TILEH; y=y+2)
    {
      TV.draw_rect(x*TILESIZE, y*TILESIZE, 2, 2, WHITE, WHITE);
    }
  }
}

/*---------------------------------------------------------------------------*/

// A debugging function.
void showPos(PositionStruct *pos)
{
  Serial.print("x=");
  Serial.print(pos->x);
  Serial.print(" y=");
  Serial.print(pos->y);

  Serial.print(" tilex=");
  Serial.print(pos->tilex);
  Serial.print(" tiley=");
  Serial.print(pos->tiley);

  Serial.print(" tileoffx=");
  Serial.print(pos->tileoffx);
  Serial.print(" tileoffy=");
  Serial.print(pos->tileoffy);

  Serial.println();
}
/*---------------------------------------------------------------------------*/

// End of PacMan.ino





















