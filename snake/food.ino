#include "food.h"

void get_legal_position(unsigned int num_of_positions, const POSITION *positions, POSITION *p_legal_position)
{
  POSITION random_position;
  bool found_legal_position = false;
  unsigned int index = 0;
  while(!found_legal_position){
    random_position.row = random(BOARD_HEIGHT);
    random_position.column = random(BOARD_WIDTH);
    found_legal_position = true;
    index = 0;
    while(found_legal_position && index < num_of_positions){
      if(positions[index].row == random_position.row && positions[index].column == random_position.column)
        found_legal_position = false;
      index++;
    }
  }
  *p_legal_position = random_position;
}

void init_food(struct FOOD *p_self, unsigned int num_of_positions, const POSITION *positions)
{
  p_self->active = true;
  p_self->timer = 0;
  get_legal_position(num_of_positions, positions, &(p_self->food_position));
}

void deactivate_food(struct FOOD *p_self)
{
  p_self->timer = random(FOOD_MIN_WAIT, FOOD_MAX_WAIT);
  p_self->active = false;
}

void update_food(struct FOOD *p_self, unsigned int num_of_positions, const POSITION *positions)
{
  if(!p_self->active){
    if(p_self->timer <= 0){
      init_food(p_self, num_of_positions, positions);
    } else{
      p_self->timer--;
    }
  }
}

void draw_food(struct FOOD *p_self)
{
  if(p_self->active)
    draw_rectangle_nokia(p_self->food_position.column * TILE_WIDTH, p_self->food_position.row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}
