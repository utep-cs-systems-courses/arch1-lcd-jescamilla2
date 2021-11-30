#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

int switches = 0;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}


void update_shape()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2; /* middle */
  static int colStep = 5, rowStep = 5; /* added (Nov 10 Lecture) */
  
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0; /* state variable */
  if (switches & SW4) return;
  if (step <= 10) { /* made object smaller from 60 to 10 (Nov 10 Lecture) */
    int startCol = col - step;
    int endCol = col + step;
    int width = 1 + endCol - startCol;
    // a color in this BGR encoding is BBBB BGGG GGGR RRRR
    unsigned int color = (blue << 11) | (green << 5) | red;

    /* added during Nov 10 Lecture */
    blue++; blue &= 31;
    green += 2; green &= 63;
    
    fillRectangle(startCol, row+step, width, 1, color);
    fillRectangle(startCol, row-step, width, 1, color);
    if (switches & SW3) green = (green + 1) % 64;
    if (switches & SW2) blue = (blue + 2) % 32;
    if (switches & SW1) red = (red - 3) % 32;
    step ++;
  } else {
    col+= colStep; row += rowStep; /* added to move center (Nov 10 Lecture) */
    if (col < 20 || col > (screenWidth - 20)) {
      col -= colStep; colStep = -colStep; /* walks to far to the right, reverse (Nov 10) */
    }
    if (row < 20 || row > (screenHeight - 20)) {
      row -= rowStep; rowStep = -rowStep; /* walks to far down, reverse (Nov 10) */
    }

    clearScreen(COLOR_BLUE);
    step = 0;
  }
}

void main(void) 
{  
  P1DIR |= LED_RED;        /* RED LED on when CPU is on */
  P1OUT |= LED_RED;

  configureClocks();       /* setup master oscillator, CPU & peripheral clocks */
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();   /* enable periodic interrupt */
  or_sr(0x18);             /* CPU off, GIE on */

  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED_RED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED_RED;	/* led on */
  }
  
} 
