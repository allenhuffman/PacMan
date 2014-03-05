#include "MazeBitmap.h"

PROGMEM const unsigned char mazeBitmap[] = {
  MAZEW, MAZEH, // 88,95,
  0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
  0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
  0x9f,0xff,0xff,0xff,0xff,0x87,0xff,0xff,0xff,0xff,0xe4,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x7f,0x88,0xff,0xe2,0x49,0x1f,0xfc,0x47,0xf8,0x94,
  0xa0,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x14,
  0xa4,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x94,
  0xae,0x80,0x49,0x00,0x12,0x49,0x20,0x02,0x48,0x05,0xd4,
  0xa4,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x94,
  0xa0,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x14,
  0xa4,0x7f,0x88,0xff,0xe2,0x31,0x1f,0xfc,0x47,0xf8,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x7f,0x88,0xc4,0x7f,0xff,0xf8,0x8c,0x47,0xf8,0x94,
  0xa0,0x80,0x41,0x20,0x80,0x00,0x04,0x12,0x08,0x04,0x14,
  0xa0,0x80,0x41,0x20,0x80,0x00,0x04,0x12,0x08,0x04,0x14,
  0xa4,0x7f,0x89,0x24,0x7f,0xcf,0xf8,0x92,0x47,0xf8,0x94,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xbf,0xff,0x89,0x1f,0xe0,0x48,0x1f,0xe2,0x47,0xff,0xf4,
  0x80,0x00,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x00,0x04,
  0x7f,0xfe,0x41,0x00,0x10,0x48,0x20,0x02,0x09,0xff,0xf8,
  0x00,0x01,0x49,0x1f,0xe0,0x30,0x1f,0xe2,0x4a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x49,0x20,0x00,0x00,0x00,0x12,0x4a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x49,0x20,0xff,0xff,0xfc,0x12,0x4a,0x00,0x00,
  0xff,0xfe,0x41,0x20,0xff,0x03,0xfc,0x12,0x09,0xff,0xfc,
  0x00,0x00,0x41,0x20,0xc0,0x00,0x0c,0x12,0x08,0x00,0x00,
  0xff,0xff,0x88,0xc0,0xc0,0x00,0x0c,0x0c,0x47,0xff,0xfc,
  0x00,0x00,0x00,0x00,0xc0,0x00,0x0c,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0xc0,0x00,0x0c,0x00,0x00,0x00,0x00,
  0x00,0x00,0x08,0x00,0xc0,0x00,0x0c,0x00,0x40,0x00,0x00,
  0x00,0x00,0x00,0x00,0xc0,0x00,0x0c,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0xc0,0x00,0x0c,0x00,0x00,0x00,0x00,
  0xff,0xff,0x88,0xc0,0xc0,0x00,0x0c,0x0c,0x47,0xff,0xfc,
  0x00,0x00,0x41,0x20,0xc0,0x00,0x0c,0x12,0x08,0x00,0x00,
  0xff,0xfe,0x41,0x20,0xff,0xff,0xfc,0x12,0x09,0xff,0xfc,
  0x00,0x01,0x49,0x20,0xff,0xff,0xfc,0x12,0x4a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x49,0x20,0x00,0x00,0x00,0x12,0x4a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x41,0x20,0x00,0x00,0x00,0x12,0x0a,0x00,0x00,
  0x00,0x01,0x49,0x20,0x7f,0xff,0xf8,0x12,0x4a,0x00,0x00,
  0x7f,0xfe,0x41,0x20,0x80,0x00,0x04,0x12,0x09,0xff,0xf8,
  0x80,0x00,0x41,0x20,0x80,0x00,0x04,0x12,0x08,0x00,0x04,
  0xbf,0xff,0x88,0xc0,0x7f,0xcf,0xf8,0x0c,0x47,0xff,0xf4,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x7f,0x88,0xff,0xe2,0x49,0x1f,0xfc,0x47,0xf8,0x94,
  0xa0,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x14,
  0xa0,0x80,0x41,0x00,0x10,0x48,0x20,0x02,0x08,0x04,0x14,
  0xa4,0x7c,0x48,0xff,0xe2,0x31,0x1f,0xfc,0x48,0xf8,0x94,
  0xa0,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x14,
  0xa4,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x94,
  0xae,0x92,0x49,0x24,0x92,0x01,0x24,0x92,0x49,0x25,0xd4,
  0xa4,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x94,
  0xa0,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x14,
  0xbe,0x12,0x48,0xc4,0x7f,0xff,0xf8,0x8c,0x49,0x21,0xf4,
  0x81,0x02,0x41,0x20,0x80,0x00,0x04,0x12,0x09,0x02,0x04,
  0x81,0x02,0x41,0x20,0x80,0x00,0x04,0x12,0x09,0x02,0x04,
  0xbe,0x11,0x89,0x24,0x7f,0x8f,0xf8,0x92,0x46,0x21,0xf4,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa0,0x00,0x01,0x20,0x00,0x48,0x00,0x12,0x00,0x00,0x14,
  0xa4,0x7f,0xff,0x3f,0xe2,0x49,0x1f,0xf3,0xff,0xf8,0x94,
  0xa0,0x80,0x00,0x00,0x10,0x48,0x20,0x00,0x00,0x04,0x14,
  0xa0,0x80,0x00,0x00,0x10,0x48,0x20,0x00,0x00,0x04,0x14,
  0xa4,0x7f,0xff,0xff,0xe2,0x31,0x1f,0xff,0xff,0xf8,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa4,0x92,0x49,0x24,0x92,0x49,0x24,0x92,0x49,0x24,0x94,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,
  0x9f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe4,
  0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
  0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0
};

// End of MazeBitmap.c
