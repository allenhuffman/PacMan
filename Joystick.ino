#include "PacMan.h"

// Modify this code to return a joystick direction, or 255 if invalid.

// Read joystick.
uint8_t readJoystick()
{
  uint16_t joy;

  joy = analogRead(JOYSTICKXPIN);
  if (joy<24)
  {
    return LEFT;
  } 
  else if (joy>1000)
  {
    return RIGHT;
  }

  joy = analogRead(JOYSTICKYPIN);
  if (joy<24)
  {
    return DOWN; // reversed on iTead Joystick Shield
  } 
  else if (joy>1000)
  {
    return UP;
  }

  // If no direction, return 255..
  return 255;
}

// End of Joystick.ino

