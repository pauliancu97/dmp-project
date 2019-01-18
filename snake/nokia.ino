#define NUM_OF_ROWS 6
#define NUM_OF_COLS 84

unsigned char screen_buffer[NUM_OF_ROWS][NUM_OF_COLS];

void init_spi()
{
  DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));// set SS, SCK, MOSI as output
  PORTB |= (1 << PB0);// set SS to HIGH (deactivate slave device)
  SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);//enable SPI, set working mode as master, set speed
}

void send_byte_spi(unsigned char chr)
{
  PORTB &= (0xFF - (1 << PB0));//clear SS, activate slave device
  SPDR = chr;//put data to send on spi data registers, this begins transmission
  while(!(SPSR & (1 << SPIF))){}//wait until transmissin finished
  PORTB |= (1 << PB0);//set SS, deactivate slave device
}

void init_nokia()
{
  init_spi();
  DDRB |= (1 << PB4) | (1 << PB5);//RST pin PB4, D/Cn pin PB5
}

void reset_nokia()
{
  PORTB &= (0xFF - (1 << PB4));//RST pin to LOW
  PORTB |= (1 << PB4);//RST pin to HIGH
}

void setup_nokia()
{
  init_nokia();
  reset_nokia();
  send_cmd_nokia(0x21);
  send_cmd_nokia(0xB8);
  send_cmd_nokia(0x04);
  send_cmd_nokia(0x14);
  send_cmd_nokia(0x20);
  send_cmd_nokia(0x0C);
  clear_nokia();
  display_nokia();
}

void send_cmd_nokia(unsigned char cmd)
{
  PORTB &= (0xFF - (1 << PB5));
  send_byte_spi(cmd);
  PORTB |= (1 << PB5);
}

void send_data_nokia(unsigned char data)
{
  PORTB |= (1 << PB5);
  send_byte_spi(data);
  
}

void clear_screen_nokia()
{
  for(unsigned short index = 0; index < 504; index++){
    send_data_nokia(0x00);
  }
}

void clear_nokia()
{
  for(unsigned char row = 0; row < NUM_OF_ROWS; row++){
    for(unsigned char column = 0; column < NUM_OF_COLS; column++){
      screen_buffer[row][column] = 0;
    }
  }
}

void display_nokia()
{
  for(unsigned char row = 0; row < NUM_OF_ROWS; row++){
    for(unsigned char column = 0; column < NUM_OF_COLS; column++){
      unsigned char set_x_cmd = (1 << 7) | (column & 0x7F);
      unsigned char set_y_cmd = 0x40 | (0x07 & row);
      send_cmd_nokia(set_x_cmd);
      send_cmd_nokia(set_y_cmd);
      send_data_nokia(screen_buffer[row][column]);
    }
  }
}

void draw_pixel_nokia(unsigned char x, unsigned char y)
{
  unsigned char vertical_byte = y / 8;
  unsigned char vertical_pixel = y % 8;
  unsigned char byte_to_send = 1 << vertical_pixel;
  unsigned char set_x_cmd = (1 << 7) | (x & 0x7F);
  unsigned char set_y_cmd = 0x40 | (0x07 & vertical_byte);
  screen_buffer[vertical_byte][x] |= byte_to_send;
}

void draw_rectangle_nokia(unsigned char x, unsigned char y, unsigned char width, unsigned char height)
{
  for(unsigned char row = y; row < y + height; row++){
    for(unsigned char col = x; col < x + width; col++){
      draw_pixel_nokia(col, row);
    }
  }
}
