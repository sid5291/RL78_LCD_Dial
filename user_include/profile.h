#ifndef PROFILE_H
#define PROFILE_H

#define PROFILE_SINGLE_TASK (0)
#define PROFILE_PRINT_ALL_REGIONS (0)

extern volatile unsigned long profile_ticks;		// total number of samples taken
extern unsigned char profiling_enabled;	// used to enable/disable profiling dynamically

extern volatile unsigned int PC_val_low;	// for debugging
extern volatile unsigned int lost; 		// most recent lost address sample;
extern volatile unsigned int num_lost; 	// total number of address samples lost


extern void Init_Profiling(void);

extern void Disable_Profiling(void);
extern void Enable_Profiling(void);
extern void Print_Results(void);
#endif
