#include "game_state.h"

void init_game_state(struct GAME_STATE *p_self, SNAKE_STATE *p_snake_state, struct FOOD *p_food)
{
  p_self->p_snake_state = p_snake_state;
  p_self->p_food = p_food;
  init_snake_state(p_self->p_snake_state);
  init_food(p_self->p_food, p_self->p_snake_state->num_of_segments, p_self->p_snake_state->segments);
  p_self->playing = true;
  p_self->timer = 0;
  p_self->score = 0;
}

void update_game_state(struct GAME_STATE *p_self)
{
  
  if(p_self->playing){
    if(is_snake_dead(p_self->p_snake_state)){
      p_self->timer = GAME_OVER_WAIT_TIME;
      p_self->playing = false;
    } else{
      POSITION snake_head_position = p_self->p_snake_state->segments[0];
      POSITION food_position = p_self->p_food->food_position; 
      if(snake_head_position.row == food_position.row && snake_head_position.column == food_position.column && p_self->p_food->active){
        add_segment_snake_state(p_self->p_snake_state);
        deactivate_food(p_self->p_food);
        p_self->score++;
      }
      update_snake_state(p_self->p_snake_state);
      update_food(p_self->p_food, p_self->p_snake_state->num_of_segments, p_self->p_snake_state->segments);
    }
  } else{
    if(p_self->timer == 0){
      init_snake_state(p_self->p_snake_state);
      init_food(p_self->p_food, p_self->p_snake_state->num_of_segments, p_self->p_snake_state->segments);
      p_self->playing = true;
      p_self->timer = 0;
      p_self->score = 0;
    } else{
      p_self->timer--;
    }
  }
}

void draw_game_state(struct GAME_STATE *p_self)
{
  clear_nokia();
  draw_snake(p_self->p_snake_state);
  draw_food(p_self->p_food);
  display_nokia();
  display_num(p_self->score);
}
