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

  // It does not matter if we are implementing a pull up or
  // pull down resistor to design a working button here, we 
  // have to clear the data direction bit for the button to
  // set it as an input. That's it.
  BIT_CLEAR(DDRB, PIN_BUTTON);
  BIT_SET(DDRD, PIN_LED);

  // If we are using a pull up here, our job will be done here
  // at this point by enabling the corresponding port bit for 
  // the button as the line below is doing.
  BIT_SET(PORTB, PIN_BUTTON);
  BIT_SET(PORTD, PIN_LED);
}

// For pull down resistors, we do the same as above in the
// code, but we do need to fiddle with our circuit a little
// bit.

// We need to supply 5V to one side of the button. On the other
// side, we need to connect the resistor to the ground, and 
// connect the same point to the input pin set for the button.

bool button_pressed(void){
  return BIT_READ(PINB, PIN_BUTTON) == 0;
}

bool button_debounced(void){
  if (button_pressed()){
    _delay_ms(1);
    if (button_pressed()){
      return button_pressed();
    }
  }
  return false;
}

int main(void){
  setup();

  while (true){
    if (button_debounced())
    {
        //BIT_SET(PORTD, PIN_LED);
        BIT_FLIP(PORTD, PIN_LED);
        state = !state;
        usart_teleplot("button state", (double) state);
    }
    //else BIT_CLEAR(PORTD, PIN_LED);
  }
  

}