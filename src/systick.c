#include "systick.h"
#include "globals.h"

#define SYSTEMTICK_PERIOD_MS  10

volatile uint32_t g_localtime;
static uint32_t g_timedelay;

void delay_1ms(uint32_t ncount)
{
    // capture the current local time
    g_timedelay = g_localtime + ncount;

    // wait until the desired delay finish
    while (g_timedelay > g_localtime);
}

void time_update(void)
{
    g_localtime += SYSTEMTICK_PERIOD_MS;
}

// NOTE: needed for lwip, declared in lwip/sys.h
uint32_t sys_now(void)
{
    return g_localtime;
}
