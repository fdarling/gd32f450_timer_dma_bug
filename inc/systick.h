#ifndef SYSTICK_H
#define SYSTICK_H

#include "gd32f4xx.h"

#include <stdint.h>

extern volatile uint32_t g_localtime; // for creating a time reference incremented by 10ms

void time_update(void); // called from SysTick interrupt

void delay_1ms(uint32_t ncount); // for delaying in units of milliseconds

inline uint64_t systick_nanoseconds(void)
{
	// read the current clock cycle time (5 ns resolution @ 200 MHz)
	uint32_t hi;
	uint32_t lo;
	int i = 5; // make sure this cannot become an infinite loop!
	do {
		hi = g_localtime;
		lo = SysTick->VAL;
	} while (g_localtime != hi && i--);
	static const uint32_t NANOSECONDS_PER_MILLISECOND = 1000000;
	static const uint32_t NANOSECONDS_PER_CLOCK_CYCLE = 5; // TODO stop hard-coding constants
	static const uint32_t SYSTICK_RELOAD_VALUE = 1999999;
	// TODO handle g_localtime 32-bit roll-over every 50 days
	const uint64_t ns = ((uint64_t)hi)*NANOSECONDS_PER_MILLISECOND + (SYSTICK_RELOAD_VALUE - lo)*NANOSECONDS_PER_CLOCK_CYCLE;
	return ns;
}

#endif // SYSTICK_H
