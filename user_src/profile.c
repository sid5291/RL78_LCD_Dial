#include <stdint.h>
#include "r_cg_timer.h"
#include "region.h"
#include "profile.h"
#include "lcd.h"

volatile unsigned long profile_ticks=0;
unsigned char profiling_enabled = 0;
volatile unsigned int PC_val_low, lost=0, num_lost=0;

void Init_Profiling(void) {
	unsigned i;

	// Clear region counts
  	for (i=0; i<NumProfileRegions; i++) {
	  	RegionCount[i]=0;
  	}

	R_TAU0_Channel0_Start();
}

void Disable_Profiling(void) {
  profiling_enabled = 0;
}

void Enable_Profiling(void) {
  profiling_enabled = 1;
}

void Clear_Lower_Screen(void) {
	unsigned line = 2;

	while (line <9) {
		LCDPrintf(line, 0, "                 ");
		line++;
	}
}

void Print_Results(void) {
	unsigned n, line=1;

	LCDFont(FONT_SMALL);
	LCDPrintf(0, 0, "%ld total ticks", profile_ticks);
	Clear_Lower_Screen();

	line++; // don't overwrite total number of ticks
	for (n=0; n<NumProfileRegions; n++) {
#if PROFILE_PRINT_ALL_REGIONS
		LCDPrintf((n%8)+1, 0, "%d %d", n, RegionCount[n]);
#else
		if (RegionCount[n] > 0) {
			LCDPrintf(line, 0, "                   ");
			LCDPrintf(line++, 0, "%d %s", RegionCount[n], RegionTable[n].Name);
		}
#endif
		if (line == 9) {
			line = 2;
			Clear_Lower_Screen();
		}
	}
}