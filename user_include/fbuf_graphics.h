#ifndef FBUF_GRAPHICS_H
#define FBUF_GRAPHICS_H
#include "lcd.h"

// function prototypes
void FBG_InitFB(void); // Initialize frame buffer with zeroes
void FBG_RefreshLCD(void)	// Transfers all frame buffer contents to LCD
void FBG_SetPixel(uint8_t x, uint8_t y, uint8_t color); // Sets pixel at x,y to color (1 or 0)
void FBG_Test(void); 	// Test function - clears LCD, draws rectangle and four diagonal lines

#endif // FBUF_GRAPHICS_H