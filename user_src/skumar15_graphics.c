#include "r_cg_macrodriver.h"
#include "math.h"
#include "r_cg_userdefine.h"
#include "lcd.h"
#include "YRDKRL78_LCD.h"
#include "fbuf_graphics.h"

#define PI      3.14159265359
#define PIx2 6.28318531
#define PIby2   1.57079632
#define PIby180 0.01745329251
#define cos1_5    0.99965732497
#define sin1_5   0.0261769483
#define ABS(a) ((a)<0?-(a):a)
#define fac_1 1
#define fac_2 2
#define fac_3 6
#define fac_4 24
#define fac_5 120
#define fac_6 720
#define fac_7 5040
#define fac_8 40320
#define fac_9 362880
#define fac_10 3628800

// Uncomment for Filled Needle (does not work properly for all angles)
//#define FILLEDNEEDLE 

void LCDDrawDialNeedle(float);
void DrawNeedleFiller(PointT, PointT, PointT, uint8_t);

float taylor_sin(float x)
{
  float sin;
if (x < -PI)
    x += PIx2;
else if (x >  PI)
    x -= PIx2;
// Quadratic Approximation
// sin = (4/pi *x + 4/pi^2 *x)
if (x < 0)
    sin = (1.27323954* x + .405284735 * x * x);
else
    sin = (1.27323954* x - 0.405284735 * x * x);
return(sin);
}

float taylor_cos(float x)
{
  float cos;
x += PIby2; // cos is sin shifted by PIby2
if (x >  PI)
    x -= PIx2;
// Quadratic Approximation
// cos = (4/pi *(x+pi/2) + 4/pi^2 *(x+pi/2)
if (x < 0)
    cos = (1.27323954 + 0.405284735 * x) * x ;
else
    cos = (1.27323954 - 0.405284735 * x) * x;

return(cos);
}

// Draw Line from p1 to p2

void LCDDrawLine(PointT *p1,PointT *p2, int8_t color,int g)
 {
    int dx = p2->X - p1->X ;
    int dy = p2->Y - p1->Y ;
    int x1 = p1->X, y1 = p1->Y;
    int x_inc1=0, x_inc2=0, y_inc1=0, y_inc2=0;
    if (dx<0) 
    {
        x_inc1 = -1; 
        x_inc2 = -1;
    }
    else if (dx>0) 
    {
        x_inc1 = 1;
        x_inc2 = 1;
    }
    else
    {
        x_inc1 = 0;
        x_inc2 = 0;
    }
    if (dy<0) 
      y_inc1 = -1;
    else if (dy>0) 
      y_inc1 = 1;
    else
      y_inc1 = 0;
    
    int length = ABS(dx);
    int width = ABS(dy);
    if (length <= width) 
    {
        length   = ABS(dy) ;
        width    = ABS(dx) ;
        if (dy<0) 
          y_inc2 = -1 ; 
        else if (dy>0) 
          y_inc2 = 1 ;
        else
          y_inc2 = 0;
        
        x_inc2 = 0 ;            
    }
    int p = length >> 1 ;
    for (int i=0;i<=length;i++) {
        FBG_SetPixel(x1,y1,color,g) ;
        p += width ;
        if (p>=length) 
        {
            p -= length ;
            x1 += x_inc1 ;
            y1 += y_inc1 ;
        } 
        else 
        {
            x1 += x_inc2 ;
            y1 += y_inc2 ;
        }
    }

}

// Draw the line from p1 to p2 but for only "steps" number of pixels
void LCDDrawLineSteps(PointT *p1, PointT *p2, uint8_t color,int steps, int g)
 {
    int dx = p2->X - p1->X ;
    int dy = p2->Y - p1->Y ;
    int x1 = p1->X, y1 = p1->Y;
    int x_inc1=0, x_inc2=0, y_inc1=0, y_inc2=0;
    if (dx<0) 
    {
        x_inc1 = -1; 
        x_inc2 = -1;
    }
    else if (dx>0) 
    {
        x_inc1 = 1;
        x_inc2 = 1;
    }
    else
    {
        x_inc1 = 0;
        x_inc2 = 0;
    }
    if (dy<0) 
      y_inc1 = -1;
    else if (dy>0) 
      y_inc1 = 1;
    else
      y_inc1 = 0;
    
    int length = ABS(dx);
    int width = ABS(dy);
    if (length <= width) 
    {
        length   = ABS(dy) ;
        width    = ABS(dx) ;
        if (dy<0) 
          y_inc2 = -1 ; 
        else if (dy>0) 
          y_inc2 = 1 ;
        else
          y_inc2 = 0;
        
        x_inc2 = 0 ;            
    }
    int p = length >> 1 ;
    for (int i=0;i<=length;i++) {
        FBG_SetPixel(x1,y1,color,g) ;
        p += width ;
        if (p>=length) 
        {
            p -= length ;
            x1 += x_inc1 ;
            y1 += y_inc1 ;
        } 
        else 
        {
            x1 += x_inc2 ;
            y1 += y_inc2 ;
        }
        if(steps == 0) break;
          steps--;
    }

}


// Draw Dial into background buffer
void LCDDrawDialBackground(void)
{
  PointT p1;
  PointT p2;
    p1.X = 0; p1.Y = 0;
    p2.X = 0; p2.Y = LCD_H-1;
    LCDDrawLine(&p1,&p2,0,1);
    p1.X = LCD_W-1; p1.Y = LCD_H-1;
    p2.X = 0; p2.Y = LCD_H-1;
    LCDDrawLine(&p1,&p2,0,1);
    p1.X = LCD_W-1; p1.Y = 0;
    p2.X = LCD_W-1; p2.Y = LCD_H-1;
    LCDDrawLine(&p1,&p2,0,1);  
    p1.X = 0; p1.Y = 0;
    p2.X = LCD_W-1; p2.Y = 0;
    LCDDrawLine(&p1,&p2,0,1);
    p2.X = 48;
    p2.Y = 39;
    for(int i=180;i<=360;i++)
    {
      p1.X = 48*taylor_cos(i*PIby180) + 48;
      p1.Y = 32*taylor_sin(i*PIby180) + 39;
      FBG_SetPixel(p1.X, p1.Y, 1,1);
      if(i%18 == 0)
      {
        LCDDrawLineSteps(&p1, &p2, 1,5,1);
      }
    }
    p1.X = 0; p1.Y = 39;
    p2.X = LCD_W-1; p2.Y = 39;
    LCDDrawLine(&p1,&p2,1,1);
}

// Draw needle at given input value on the Dial
void LCDDrawDialNeedle(float input_value)
{
int e_x = 0, e_y = LCD_H>>2;
int i_x = (LCD_W>>2)+8, i_y = (LCD_H>>2);
int l_x = (LCD_W>>2), l_y = (LCD_H>>2)+4;
int r_x = (LCD_W>>2), r_y = (LCD_H>>2)-4;
float theta = 180+ (18 * (input_value));
PointT p1;
PointT p2,p3,p4;
e_x = 48*taylor_cos(theta*PIby180) + 48;
e_y = 32*taylor_sin(theta*PIby180) + 39;
i_x = 8*taylor_cos(((theta-180)*PIby180)) + 48;
i_y = 5.3*taylor_sin(((theta-180)*PIby180)) + 39; // 2/3 of 8
l_x = 4*taylor_cos(((theta+90)*PIby180)) + 48;
l_y = 2.6*taylor_sin(((theta+90)*PIby180)) + 39; // 2/3 of 4
r_x = 4*taylor_cos(((theta-90)*PIby180)) + 48;
r_y = 2.6*taylor_sin(((theta-90)*PIby180)) + 39; // 2/3 of 4
p1.X = e_x; p1.Y = e_y;
p2.X = r_x; p2.Y = r_y;
p4.X = i_x; p4.Y = i_y;
p3.X = l_x; p3.Y = l_y;
LCDDrawLine(&p1,&p2,1,2);
LCDDrawLine(&p1,&p3,1,2);
LCDDrawLine(&p4,&p3,1,2);
LCDDrawLine(&p4,&p2,1,2);
#ifdef FILLEDNEEDLE
DrawNeedleFiller(p1,p2,p3,1);
DrawNeedleFiller(p2,p3,p4,1);
#endif
}

#ifdef FILLEDNEEDLE
// Fill triangle denoted by p1,p2,p3 with color
void DrawNeedleFiller(PointT p1, PointT p2, PointT p3, uint8_t color)
{
  int x1,x2,x3,y1,y2,y3;
  int dx1,dx2,dx3;
  if(p1.Y <= p2.Y)
  {
    if(p1.Y <= p3.Y)
    { y1 = p1.Y; x1 = p1.X;
      if(p2.Y <= p3.Y)
      {
         y2 = p2.Y; x2 = p2.X;
         y3 = p3.Y; x3 = p3.X;}
      else
      {  y3 = p2.Y; x3 = p2.X;
         y2 = p3.Y; x2 = p3.X;}
    }
    else
    { y1 = p3.Y; x1 = p3.X;
      y2 = p1.Y; x2 = p1.X;
      y3 = p2.Y; x3 = p2.X;}
  }
  else
  {
    if(p2.Y <= p3.Y)
    { y1 = p2.Y; x1 = p2.X;
      if(p1.Y <= p3.Y)
      {
         y2 = p1.Y; x2 = p1.X;
         y3 = p3.Y; x3 = p3.X;}
      else
      {  y3 = p1.Y; x3 = p1.X;
         y2 = p3.Y; x2 = p3.X;}
    }
    else
    { y1 = p3.Y; x1 = p3.X;
      y2 = p2.Y; x2 = p2.X;
      y3 = p1.Y; x3 = p1.X;}
  }
PointT e,s;
e.X = x1;
e.Y = y1;
s.X = x1;
s.Y = y1;
 if (y2 - y1 > 0) dx1=(x2-x1)/(y2-y1); else dx1=0;
 if (y3 - y1 > 0) dx2=(x3-x1)/(y3-y1); else dx2=0;
 if (y3 - y2 > 0) dx3=(x3-x2)/(y3-y2); else dx3=0;

 if(dx1 > dx2) {
		while(s.Y<=y2)
                {       s.Y++;e.Y=s.Y;s.X+=dx2;e.X+=dx1;
			 LCDDrawLine(&s,&e,1,2);
                }
		e.X = x2; e.Y = y2;
		while(s.Y<=y3)
                {       s.Y++;e.Y=s.Y;s.X+=dx2;e.X+=dx3; 
			 LCDDrawLine(&s,&e,1,2);
                }
	} 
 else   {
		while(e.Y<=y2)
                {       s.Y++;e.Y=s.Y;s.X+=dx1;e.X+=dx2;
			 LCDDrawLine(&s,&e,1,2);
                }
		s.X = x2; s.Y = y2;
		while(e.Y<=y3)
                {       s.Y++;e.Y=s.Y;s.X+=dx3;e.X+=dx2;
			 LCDDrawLine(&s,&e,1,2);
                }
	}
}

#endif

void TestMyCode()  // Test Code for Dial
{
FBG_InitFB  ();
LCDDrawDialBackground(); 
FBG_RefreshLCD_BG();
for(float i = 0; i<10.0;i=i+0.1)
  {    
    LCDDrawDialNeedle(i);
    FBG_RefreshLCD_FG();
  }
}