// Frame Buffer Graphics
#include "r_cg_macrodriver.h"
#include "lcd.h"
#include "YRDKRL78_LCD.h"
#include "fbuf_graphics.h"

static uint8_t fbuf[LCD_W][LCD_H/8];            // Frame buffer
static uint8_t fbuf_BG[LCD_W][LCD_H/8];        // Background Frame buffer
static uint8_t fbuf_FG[LCD_W][LCD_H/8];        // Foreground Frame Buffer   
static uint8_t fbuf_FG_prev[LCD_W][LCD_H/8];  // Previous Foreground frame buffer
static uint8_t fbuf_chk[LCD_W][LCD_H];       // Each pixel bit check
static uint8_t fbuf_chk_bg[LCD_W][LCD_H/8]; // Background Buffer Valid bit
static uint8_t fbuf_chk_fg[LCD_W][LCD_H/8]; // Foreground buffer Valid bit


void FBG_InitFB(void) {             // Initialize frane buffers
	uint8_t x, y;

	for (x=0; x<LCD_W; x++) {
		for (y=0; y<LCD_H/8; y++) {
			fbuf_BG[x][y] = 0;
                        fbuf_FG[x][y] = 0;
                        fbuf_chk[x][y] = 0;
		}
	}
       
}

void FG_ClearFB(void)  // Clear current Foreground buffer,
{                          // Store Previous buffer
	uint8_t x, y;

	for (x=0; x<LCD_W; x++) {
		for (y=0; y<LCD_H/8; y++) 
                {       if(fbuf_FG[x][y] != 0) 
                        {
                          fbuf_FG_prev[x][y] = fbuf_FG[x][y];
                          fbuf_FG[x][y] = 0;
                        }
                        else
                          fbuf_chk_fg[x][y] = 0;
		}
	}
       
}

void FBG_RefreshLCD(void) {  // LCD frame buffer refresh
	uint8_t x, y;
	for (y=0; y<LCD_H/8; y++) {
		// set row (page) address in DDRAM
		YRDKRL78_CommandSend(0x40|y);

		// set column address in DDRAM to 0
		//YRDKRL78_CommandSend(0x80);
                
		for (x=0; x<LCD_W; x++) {
			// write data to DDRAM
			// column number is autoincremented in LCD controller IC
                  if(fbuf_chk[x][y] != 0)
                 {      YRDKRL78_CommandSend(0x80|x);
			YRDKRL78_DataSend(fbuf[x][y]);
                        fbuf_chk[x][y] = 0;
                  }
		}
	}
}

void FBG_RefreshLCD_BG(void) {  // Background Buffer Refresh
	uint8_t x=0, y,i=0;
	for (y=0; y<LCD_H/8; y++) {
		// set row (page) address in DDRAM
		YRDKRL78_CommandSend(0x40|y);

		// set column address in DDRAM to 0
		//YRDKRL78_CommandSend(0x80);
                x = 0;
		while(x<LCD_W) {
                  if(fbuf_chk_bg[x][y] == 1)
                 {      if(x-i != 1)// column number is autoincremented in LCD controller IC   
                          {
                            YRDKRL78_CommandSend(0x80|x);// write data to DDRAM
                            i = x;
                          }
			YRDKRL78_DataSend(fbuf_BG[x][y]);
                  }
                  x++;
		}
	}
}
void FBG_RefreshLCD_FG(void) {  // Forefround buffer refresh
	uint8_t x=0, y,i=0;
      
	for (y=0; y<LCD_H/8; y++) 
        {
		YRDKRL78_CommandSend(0x40|(y));
                x =0;
		while(x<LCD_W)
                {			
                  if((fbuf_chk_fg[x][y] == 1) && (fbuf_FG_prev[x][y] != fbuf_FG[x][y]))
                 {      if(x-i != 1) // column number is autoincremented in LCD controller IC
                          {
                            YRDKRL78_CommandSend(0x80|x); // write data to DDRAM 
                            i = x;
                          }
			YRDKRL78_DataSend(fbuf_FG[x][y]|fbuf_BG[x][y]);
                  }
                  x++;
		}
	}
        FG_ClearFB();
}


void FBG_SetPixel_BG(uint8_t x, uint8_t y, uint8_t color) { // Backgrounf buffer set pixel
	uint8_t row = y>>3;
	if ((x < LCD_W) & (y < LCD_H)) {
          fbuf_chk[x][y] = 2;
          fbuf_chk_bg[x][row] = 1;
		if (color) {
			fbuf_BG[x][row] |= 1<<(y&0x07);
		} else {
			fbuf_BG[x][row] &= ~(1<<(y&0x07));
		}
	}
}


// Set Pixel which allows choice of foregrond(2) and background(1) buffer
void FBG_SetPixel(uint8_t x, uint8_t y, uint8_t color,int g) 
{
	uint8_t row = y>>3;
        
        if(g==2) //Foreground
        {  
	if ((x < LCD_W) & (y < LCD_H)) {
         fbuf_chk_fg[x][row] = 1;
		if (color) {
			fbuf_FG[x][row] |= 1<<(y&0x07);
		} else {
			fbuf_FG[x][row] &= ~(1<<(y&0x07));
		}
	}
        }
        else if(g==1)  //Background
        {
          if ((x < LCD_W) & (y < LCD_H)) {
          fbuf_chk_bg[x][row] = 1;
		if (color) {
			fbuf_BG[x][row] |= 1<<(y&0x07);
		} else {
			fbuf_BG[x][row] &= ~(1<<(y&0x07));
		}
	}
        }
}


/*
void FBG_SetPixel(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t row = y>>3;
	if ((x < LCD_W) & (y < LCD_H)) {
          fbuf_chk[x][row] = 1;
		if (color) {
			fbuf[x][row] |= 1<<(y&0x07);
		} else {
			fbuf[x][row] &= ~(1<<(y&0x07));
		}
	}
}

void FBG_Test(void) {
	uint8_t n;

	FBG_InitFB();
	for (n=0; n<LCD_W; n++) {
		FBG_SetPixel(n, 0, 1);
		FBG_SetPixel(n, LCD_H-1, 1);
	}

	for (n=0; n<LCD_H; n++) {
		FBG_SetPixel(n, n, 1);
		FBG_SetPixel(n, LCD_H-n-1, 1);
		FBG_SetPixel(n+(LCD_W-LCD_H), n, 1);
		FBG_SetPixel(n+(LCD_W-LCD_H), LCD_H-n-1, 1);
		FBG_SetPixel(0, n, 1);
		FBG_SetPixel(LCD_W-1, n, 1);
	}
	FBG_RefreshLCD();
}
*/