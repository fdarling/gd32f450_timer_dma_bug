#ifndef GLOBALS_H
#define GLOBALS_H

#include "gd32f4xx.h"

#include <stdint.h>

static const uint32_t TIMER_DMA_INSTANCE = DMA1;
static const rcu_periph_enum TIMER_DMA_CLK = RCU_DMA1;
//static const dma_channel_enum TIMER_DMA_CHANNEL = DMA_CH1;
//static const dma_subperipheral_enum TIMER_DMA_SUBPER = DMA_SUBPERI7; // TIMER7_UP
static const dma_channel_enum TIMER_DMA_CHANNEL = DMA_CH2;
static const dma_subperipheral_enum TIMER_DMA_SUBPER = DMA_SUBPERI7; // TIMER7_CH0
static const uint32_t TIMER_INSTANCE = TIMER7;
static const rcu_periph_enum TIMER_CLK = RCU_TIMER7;
static const dbg_periph_enum TIMER_HOLD = DBG_TIMER7_HOLD;

#define SG_BUFFER_SIZE (32)

extern volatile uint32_t period_buffer[SG_BUFFER_SIZE];

#endif // GLOBALS_H
