#include "digits_display.h"

#define OE_PIN 1 << 0
#define DS_PIN 1 << 1
#define SHCP_PIN 1 << 2
#define STCP_PIN 1 << 3

const unsigned char ssdlut[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

volatile unsigned char display_digits[4];
volatile unsigned char display_digit_index = 0;

void setup_serial_to_parallel_pins()
{
  DDRC = 0;//clear direction register for portb
  DDRC |= OE_PIN | DS_PIN | SHCP_PIN | STCP_PIN;// set the oe, ds, shcp, stcp pins to be outputs
  PORTC = 0;//make values of all output pins to be LOW
  PORTC |= OE_PIN;// set the value of oe pin to be HIGH
}

void setup_digits_dispaly_pins()
{
  DDRA = 0;
  DDRA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3);
  PORTA = 0;
  PORTA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3);
}

void calculate_digits(unsigned int short num, volatile unsigned char digits[])
{
  digits[0] = num % 10;
  digits[1] = (num / 10) % 10;
  digits[2] = (num / 100) % 10;
  digits[3] = num / 1000;
}

void display_num(unsigned short num)
{
  calculate_digits(num, display_digits);
}

void set_up_timer1(unsigned char cmp)
{
  cli(); 
  TCCR1A = 0; 
  TCCR1B = 0;
  OCR1A = cmp;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect)
{
  PORTA = 0x0F - (1 << display_digit_index);
  send_char(ssdlut[display_digits[3 - display_digit_index]]);
  if(display_digit_index == 3){
    display_digit_index = 0;
  } else{
    display_digit_index++;
  }
}

void send_char(unsigned char chr)
{
  PORTC |= OE_PIN;//set OE pin
  PORTC &= (0xFF - SHCP_PIN);//clear SHCP pin
  PORTC &= (0xFF - STCP_PIN);//clear STCP pin
  for(unsigned char index = 0; index < 8; index++){
    PORTC &= (0xFF - SHCP_PIN);//clear SHCP pin
    if(chr & (1 << 7)){//if MSB = HIGH
      PORTC |= DS_PIN;// set DS pin
    }
    else{
      PORTC &= (0xFF - DS_PIN);//clear DS pin
    }
    PORTC |= SHCP_PIN;//set SHCP pin
    chr = chr << 1;//shift chr
  }
  PORTC |= STCP_PIN;//set STCP pin
  PORTC &= (0xFF - OE_PIN);// clear OE pin
  
}

void setup_digits_display() {
  // put your setup code here, to run once:
  setup_serial_to_parallel_pins();
  setup_digits_dispaly_pins();
  set_up_timer1(16);
}
