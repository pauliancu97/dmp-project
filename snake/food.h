#pragma once

#include "utils.h"
#include "board.h"
#include "nokia.h"

#define FOOD_MIN_WAIT 5
#define FOOD_MAX_WAIT 10

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

struct FOOD{
  POSITION food_position;
  bool active;
  int timer;
};

void init_food(struct FOOD *, unsigned int, const POSITION *);
void deactivate_food(struct FOOD *);
void update_food(struct FOOD *, unsigned int, const POSITION *);
void draw_food(struct FOOD *);
