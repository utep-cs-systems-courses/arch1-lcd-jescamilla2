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

  int startCol;
  int endCol;
  int startRow;
  int endRow;
  int height = 1 + endRow - startRow;
  int width = 1 + endCol - startCol;

  // a color in this BGR encoding is BBBB BGGG GGGR RRRR
  unsigned int color = (blue << 11) | (green << 5) | red;

  
  if (switch1_state_down) {

    for (int step = 0; step <= 50; step++) {
      startCol = col - step;
      endCol = col + step;
      startRow = row - 10;
      endRow = row + 10;
      height = 1 + endRow - startRow;
      width = 1 + endCol - startCol;

      /* blue++; blue &= 31; */
      /* green += 2; green &= 63; */
    
      fillRectangle(startCol, row - 25 + step, width, 1, color);
    }
    
  } else if (switch2_state_down) {
    if (step <= 10) { 

      startCol = col - step;
      endCol = col + step;
      startRow = row - step;
      endRow = row + step;
      width = 1 + endCol - startCol;
      height = 1 + endRow - startRow;

      blue++; blue &= 31;
      green += 2; green &= 63;


      fillRectangle(col + 10 - step, startRow, 1, height, color);
      fillRectangle(col - 10 + step, startRow, 1, height, color);
      fillRectangle(startCol, row + 10 -step, width, 1, color);
      fillRectangle(startCol, row - 10 +step, width, 1, color);
      step++;
    } else {
      col+= colStep; row += rowStep; /* added to move center */
      if (col < 20 || col > (screenWidth - 20)) {
	col -= colStep; colStep = -colStep; /* walks too far to the right, reverse */
      }
      if (row < 20 || row > (screenHeight - 20)) {
	row -= rowStep; rowStep = -rowStep; /* walks too far down, reverse */
      }
      clearScreen(COLOR_BLUE);
      step = 0;
    }
  } else if (switch3_state_down) {

    row = screenHeight /2;
    col = screenHeight /2;
    
    /* display message on screen */
    drawString5x7(0 , row - 50, "Hello, world!", COLOR_WHITE, COLOR_BLACK);
    
  } else if (switch4_state_down) {
      clearScreen(COLOR_BLUE);
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
