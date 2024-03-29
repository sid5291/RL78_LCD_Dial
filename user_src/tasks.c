#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

#include "profile.h"
#include "rtc_sched.h"
#include "lcd.h"

void Task1(void) {
	static char led_state=0;

	LED_4_G = led_state;
	led_state ^= 1;
}

void Task2(void) {
	static char led_state=0;

	LED_6_G = led_state;
	led_state ^= 1;
}

// Task3 runs at 1 Hz, updates elapsed time on LCD
void Task3(void) {
	static char led_state=0;
	static unsigned char m=0, s=0;

	LED_8_G = led_state;
	led_state ^= 1;

	s++;
	if (s>59) {
		m++;
		s = 0;
	}

	if (!SW_1) {		// Display profile info if SW1 pressed
		Disable_Profiling();
		Print_Results();
		// hold until switch is released
		while (!SW_1)
			;
		LCDClearScreen(); // erase screen
	}
	LCDPrintf(2,0, "%02u:%02u", m, s);
}
