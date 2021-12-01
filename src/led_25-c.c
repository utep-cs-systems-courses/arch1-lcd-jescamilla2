#include <msp430.h>
#include "stateMachines.h"
#include "led.h"


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
