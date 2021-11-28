/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  short col = 30, row = 30;
  short start_col = SHORT_EDGE_PIXELS/2, start_row = LONG_EDGE_PIXELS/2;

  for (col = 0; col < 30;) {
    short leftEdge = -col;
    short rightEdge = col;

    for (short c = leftEdge; c <= rightEdge; c++) {
      drawPixel(start_col + c, start_row + row, COLOR_PINK);
    }
    col += 1; row -= 1;
  }
  
  /* drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED); */

  /* fillRectangle(30,30, 60, 60, COLOR_ORANGE); */
  
}
