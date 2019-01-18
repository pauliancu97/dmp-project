#pragma once

#include "utils.h"
#include "board.h"
#include "nokia.h"

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define MAX_SNAKE_NUM_OF_SEGMENTS 1024

#define SEGMENT_WIDTH 4
#define SEGMENT_HEIGHT 4

#define DELAY 500

typedef struct _SNAKE_STATE{
  DIRECTION snake_direction;
  unsigned short num_of_segments;
  POSITION segments[MAX_SNAKE_NUM_OF_SEGMENTS];
} SNAKE_STATE;

void init_snake_state(SNAKE_STATE *);
bool is_snake_dead(SNAKE_STATE *);
void add_segment_snake_state(SNAKE_STATE *);
void update_snake_state(SNAKE_STATE *);
void draw_snake(SNAKE_STATE *p_snake_state);
