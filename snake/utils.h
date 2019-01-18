#pragma once

#define TILE_WIDTH 4
#define TILE_HEIGHT 4

typedef enum _DIRECTION{
  UP,
  DOWN,
  LEFT,
  RIGHT
} DIRECTION;

typedef struct _POSITION{
  unsigned short row;
  unsigned short column;
} POSITION;
