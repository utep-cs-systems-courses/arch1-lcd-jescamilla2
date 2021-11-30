#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

int blink_count = 0;
int main_state = 0;
int intensity_state = 1;
int fast_state = 0;  

void light_25(int state) {
  switch(state) {
  case 0:
  case 1:
  case 2:
    P1OUT &= ~LED_GREEN; // turning off led green
    break;
  case 3:
    P1OUT |= LED_GREEN; // turn on led green
  default:
    break;
  }
}

void light_50(int state) {
  switch(state) {
  case 0:
  case 1:
    P1OUT &= ~LED_GREEN; // turning off led green
    break;
  case 2:
  case 3:
    P1OUT |= LED_GREEN; // turn on led green
  default:
    break;
  }
}

void light_75(int state) {
  switch(state) {
  case 0:
    P1OUT &= ~LED_GREEN; // turning off led green
    break;
  case 1:
  case 2:
  case 3:
    P1OUT |= LED_GREEN; // turn on led green
  default:
    break;
  }
}

void light_on(int state) {
  P1OUT |= LED_GREEN; // turn on led green
}
 
void state_advance(int blink_count)
{
  blink_count++;
  if (blink_count >= 250) {
    main_state ^= 1; // alternating between 1 and 0
  }

  if (main_state == 0) {
    P1OUT &= ~LED_GREEN;  // turn off led
    return;
  }

  if (blink_count >= 500) {
    intensity_state = (intensity_state % 4) + 1;
    blink_count = 0;
  }

  fast_state = (fast_state + 1) % 4;
  switch(intensity_state) {
  case 1: light_25(fast_state); break;
  case 2: light_50(fast_state); break;
  case 3: light_75(fast_state); break;
  case 4: light_on(fast_state); break;
  default: break;
  }

  /*  // this was an alternate way to incorporate the state machines done in lab */
  /* if (fast_state >= intensity_state) { */
  /*   P1OUT |= LED_GREEN * main_state; */
  /* } else { */
  /*   P1OUT &= ~LED_GREEN; */
  /* } */
  
}




