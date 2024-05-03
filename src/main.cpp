#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "bit.h"
#include "usart.h"

#define F_CLK 16000000UL
#define BAUD_RATE 9600

#define PIN_BUTTON PINB0
#define PIN_LED PIND6

bool state;

void setup(void){
  usart_init(BAUD_RATE);

  BIT_CLEAR(DDRB, PIN_BUTTON);
  BIT_SET(DDRD, PIN_LED);

  BIT_SET(PORTB, PIN_BUTTON);
  BIT_SET(PORTD, PIN_LED);
}

bool button_pressed(void){
  return BIT_READ(PINB, PIN_BUTTON) == 0;
}

bool button_debounced(void){
  if (button_pressed()){
    _delay_ms(1);
    if (button_pressed()){
      return button_pressed();
    }
    return false;
  }
}

int main(void){
  setup();

  while (true){
    if (button_debounced())
    {
        BIT_SET(PORTD, PIN_LED);
        //BIT_FLIP(PORTD, PIN_LED);
    }
    else BIT_CLEAR(PORTD, PIN_LED);
  }
  

}