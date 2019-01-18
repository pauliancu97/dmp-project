#include "snake_state.h"


void snake_state_up_direction(SNAKE_STATE *p_snake_state)
{
  if(p_snake_state->segments[0].row != 0){
    p_snake_state->segments[0].row--;
  }
  else{
    p_snake_state->segments[0].row = BOARD_HEIGHT - 1;
  }
}

void snake_state_down_direction(SNAKE_STATE *p_snake_state)
{
  if(p_snake_state->segments[0].row != BOARD_HEIGHT - 1){
    p_snake_state->segments[0].row++;
  }
  else{
    p_snake_state->segments[0].row = 0;
  }
}

void snake_state_left_direction(SNAKE_STATE *p_snake_state)
{
  if(p_snake_state->segments[0].column != 0){
    p_snake_state->segments[0].column--;
  }
  else{
    p_snake_state->segments[0].column = BOARD_WIDTH - 1;
  }
}

void snake_state_right_direction(SNAKE_STATE *p_snake_state)
{
  if(p_snake_state->segments[0].column != BOARD_WIDTH - 1){
    p_snake_state->segments[0].column++;
  }
  else{
    p_snake_state->segments[0].column = 0;
  }
}

void init_snake_state(SNAKE_STATE *p_self)
{
  p_self->snake_direction = RIGHT;
  p_self->num_of_segments = 3;
  p_self->segments[0].row = 0; p_self->segments[0].column = 3;
  p_self->segments[1].row = 0; p_self->segments[1].column = 2;
  p_self->segments[2].row = 0; p_self->segments[2].column = 1;
}

bool is_snake_dead(SNAKE_STATE *p_self)
{
  POSITION head_position = p_self->segments[0];
  for(unsigned short index = 1; index < p_self->num_of_segments; index++){
    POSITION tail_position = p_self->segments[index];
    if(head_position.row == tail_position.row && head_position.column == tail_position.column){
      return true;
    }
  }
  return false;
}

void add_segment_snake_state(SNAKE_STATE *p_self)
{
  p_self->num_of_segments++;
}

void update_snake_state(SNAKE_STATE *p_snake_state)
{
  for(unsigned short index = p_snake_state->num_of_segments - 1; index >= 1; index--)
  {
    p_snake_state->segments[index].row = p_snake_state->segments[index - 1].row;
    p_snake_state->segments[index].column = p_snake_state->segments[index - 1].column;
  }
  switch(p_snake_state->snake_direction)
  {
    case UP:
      snake_state_up_direction(p_snake_state);
      break;
    case DOWN:
      snake_state_down_direction(p_snake_state);
      break;
    case LEFT:
      snake_state_left_direction(p_snake_state);
      break;
    case RIGHT:
      snake_state_right_direction(p_snake_state);
      break;
  }
}

void draw_snake(SNAKE_STATE *p_snake_state)
{
  for(unsigned int y = 0; y < BOARD_HEIGHT; y++){
      for(unsigned int x = 0; x < BOARD_WIDTH; x++){
        for(unsigned int segment_index = 0; segment_index < p_snake_state->num_of_segments; segment_index++){
          if(y == p_snake_state->segments[segment_index].row && x == p_snake_state->segments[segment_index].column){
            draw_rectangle_nokia(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
          }
        }
      }
  }
}
