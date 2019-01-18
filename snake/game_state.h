#pragma once

#include "utils.h"
#include "board.h"
#include "snake_state.h"
#include "food.h"
#include "digits_display.h"

#define GAME_OVER_WAIT_TIME 5

struct GAME_STATE{
  SNAKE_STATE *p_snake_state;
  struct FOOD *p_food;
  bool playing;
  unsigned long timer;
  unsigned int score;
};

void init_game_state(struct GAME_STATE *, SNAKE_STATE *, struct FOOD *);
void update_game_state(struct GAME_STATE *);
void draw_game_state(struct GAME_STATE *);
