#define UP_ARROW 1 << PD0 //PINA0
#define DOWN_ARROW 1 << PD1 //PINA1
#define LEFT_ARROW 1 << PD2 //PINA2
#define RIGHT_ARROW 1 << PD3 //PINA3

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "snake_state.h"
#include "food.h"
#include "board.h"
#include "game_state.h"
#include "digits_display.h"

SNAKE_STATE snake_state;
struct FOOD food;
struct GAME_STATE game_state;


void setup_input_buttons()
{
  DDRD = 0;//set all pins for PORTD as input
  PORTD = 0;//disable pull up resistors for PORTD pins
  PORTD |= ((1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3));//set pullup resistors for PORTD0,1,2,3 
  cli();// disable interrupts for setup 
  //activate interrupts for pins corresponding to buttons
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
  EIMSK |= (1 << INT2);
  EIMSK |= (1 << INT3);
  //interrupt mode, falling edge for all buttons' pins
  EICRA |= (1 << ISC01);
  EICRA |= (1 << ISC11);
  EICRA |= (1 << ISC21);
  EICRA |= (1 << ISC31);
  sei();// enable interrupts back on
}

ISR(INT0_vect)
{
  if(snake_state.snake_direction != DOWN)
    snake_state.snake_direction = UP;
}

ISR(INT1_vect)
{
  if(snake_state.snake_direction != UP)
    snake_state.snake_direction = DOWN;
}

ISR(INT2_vect)
{
  if(snake_state.snake_direction != RIGHT)
    snake_state.snake_direction = LEFT;
}

ISR(INT3_vect)
{
  if(snake_state.snake_direction != LEFT)
    snake_state.snake_direction = RIGHT;
}

void test()
{
  snake_state.snake_direction = RIGHT;
  snake_state.num_of_segments = 6;
  snake_state.segments[0].row = 0; snake_state.segments[0].column = 3;
  snake_state.segments[1].row = 1; snake_state.segments[1].column = 3;
  snake_state.segments[2].row = 1; snake_state.segments[2].column = 2;
  snake_state.segments[3].row = 2; snake_state.segments[3].column = 2;
  snake_state.segments[4].row = 2; snake_state.segments[4].column = 1;
  snake_state.segments[5].row = 2; snake_state.segments[5].column = 2;
}

void setup() {
  // put your setup code here, to run once:
  //test();
  //init_food(&food, snake_state.num_of_segments, snake_state.segments);
  init_game_state(&game_state, &snake_state, &food);
  Serial.begin(9600);
  setup_digits_display();
  setup_nokia();
  setup_input_buttons();

}

void loop() {
  update_game_state(&game_state);
  //update_snake_state(&snake_state);
  //update_food(&food, snake_state.num_of_segments, snake_state.segments);
  //snake_display.clearDisplay();
  //draw_snake(&snake_state, snake_display);
  //draw_food(&food, snake_display);
  //snake_display.display();
  draw_game_state(&game_state);
  delay(DELAY);
}
