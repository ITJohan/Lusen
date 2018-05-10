#include "delays.h"
#include "defines.h"

void delay_250ns(void) {
	*STK_CTRL = 0;				// clear SysTik
	*STK_LOAD = 41;				// initialize with 42 cycles
	*STK_VAL = 0;				// clear countregister
	*STK_CTRL = 5;				// reset counter
	while ((*STK_CTRL & 0x00010000) == 0) {}	// wait until COUNTFLAG = 1
	*STK_CTRL = 0;				// clear SysTik
}

void delay_500ns(void) {
	delay_250ns();
	delay_250ns();
}

void delay_micro(unsigned int us) {
	while(us--) {
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
	} 
}

void delay_milli(unsigned int ms) {
//	#ifdef SIMULATOR
		while( ms-- )
			delay_micro(1);
//	#else
//		while( ms-- )
//			delay_micro(1000);
//	#endif
}
