#include <msp430.h>
#include "led.h"
#include "switches.h"


/* void led_init() */
/* { */
/*   P1DIR |= LEDS;// bits attached to leds are output */
/*   switch_state_changed = 1; */
/*   led_update(); */
/* } */

/*
void led_update(){
  if (switch_state_changed) {
    char ledFlags = 0; // by default, no LEDs on 

    ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;

    P2OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P2OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;
}
*/


void led_init()
{
  P1DIR |= LEDS;             // Set LEDS to be outputs
  P1OUT &= ~LED_GREEN;       // Turn off green LED
  P1OUT |= LED_RED;          // Turn on red LED
}

void led_off()
{
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
}
