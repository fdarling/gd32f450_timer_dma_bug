#include "main.h"
#include "globals.h"
#include "systick.h"
#include "gd32f4xx.h"

#include <stdio.h>
#include <inttypes.h>

// test case options
#define DMA_WRITE_CAR (0)
#define DMA_WRITE_CH2CV (1)
#define DMA_WRITE_PSC (2)
#define DMA_WRITE_CAR_INDIRECT (3)
#define DMA_WRITE_CH2CV_INDIRECT (4)
#define DMA_WRITE_PSC_INDIRECT (5)
#define DMA_WRITE_CAR_WITH_CPU (6)

// test case selection
#define TIMER_WRITE_TESTCASE DMA_WRITE_CAR

// PA9: USART0_TX
// PA10: USART0_RX
// PC6: TIMER7_CH0
// PC7: TIMER7_CH1
// PC8: TIMER7_CH2
// PC9: TIMER7_CH3
// PA0: debug GPIO
// PA3: debug GPIO
// PA4: debug GPIO
// PA5: debug GPIO

// global function forward declarations
int _write(int file, char *ptr, int len) __attribute__((used));

// forward declarations
static void rcu_config(void);
static void dbg_config(void);
static void gpio_config(void);
static void uart_config(void);
static void systick_config(void);
static void timer_config(void);
static void dma_config(void);

int main(void)
{
	rcu_config();
	dbg_config();
	gpio_config();
    uart_config();
    systick_config();
    timer_config();
    dma_config();

    printf("\e[2J\e[HGD32F450 timer bug test firmware booted!\r\n");

    // fill the DMA memory source buffer (values are period, duty cycle, or prescalar depending on the test case)
    for (int i = 0; i < SG_BUFFER_SIZE; i++)
	{
		period_buffer[i] = (i%16)*20;
	}

    // turn on DMA and then the timer triggering it
#if (TIMER_WRITE_TESTCASE != DMA_WRITE_CAR_WITH_CPU)
    dma_channel_enable(TIMER_DMA_INSTANCE, TIMER_DMA_CHANNEL);
#endif // TIMER_WRITE_TESTCASE

    // debug GPIO pulse to show that we're about to enable the timer (which will trigger DMA)
    GPIO_BOP(GPIOA) = GPIO_BOP_BOP0;
    GPIO_BOP(GPIOA) = GPIO_BOP_CR0;
    timer_enable(TIMER_INSTANCE);

    printf("Entering while (1) loop...\r\n");
#if (TIMER_WRITE_TESTCASE == DMA_WRITE_CAR_WITH_CPU)
    while (1)
    {
    	// GPIO pulse for debugging
    	GPIO_BOP(GPIOA) = GPIO_BOP_BOP0;
    	GPIO_BOP(GPIOA) = GPIO_BOP_CR0;

    	// wait for the timer's count to be below 200 (far away from period we are writing)
    	while (TIMER_CNT(TIMER_INSTANCE) > 200);

    	// update the period to a low value
    	TIMER_CAR(TIMER_INSTANCE) = 799-400;

    	// make sure we get above a count of 200 so we don't accidentally double-trigger within the same counter period
    	for (volatile int i = 0; i < 400; i++) {}

    	// GPIO pulse for debugging
    	GPIO_BOP(GPIOA) = GPIO_BOP_BOP0;
    	GPIO_BOP(GPIOA) = GPIO_BOP_CR0;

    	// wait for the timer's count to be below 200 (far away from period we are writing)
    	while (TIMER_CNT(TIMER_INSTANCE) > 200);

    	// update the period to a high value
    	TIMER_CAR(TIMER_INSTANCE) = 799+400;

    	// make sure we get above a count of 200 so we don't accidentally double-trigger within the same counter period
    	for (volatile int i = 0; i < 400; i++) {}
    }
#else // if (TIMER_WRITE_TESTCASE != DMA_WRITE_ADDR_CAR_WITH_CPU)
    while (1)
    {
    	const uint32_t cnt = TIMER_CNT(TIMER_INSTANCE);
    	printf("TIMER8->CNT = %10" PRId32 "\r\n", cnt);
    	delay_1ms(250);
    }
#endif // TIMER_WRITE_TESTCASE
}

static void rcu_config(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_SYSCFG);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(TIMER_DMA_CLK);
	rcu_periph_clock_enable(TIMER_CLK);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // TODO is this necessary?
}

static void dbg_config(void)
{
	dbg_deinit();
	dbg_periph_enable(TIMER_HOLD);
}

static void gpio_config(void)
{
    /// UART

    // TX pin
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    // RX pin
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /// StepGen

	// for stepgen timer PWM debug outputs
	gpio_af_set(GPIOC, GPIO_AF_3, GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6);
	gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6);
	gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6);

	// for timing function calls
	static const uint32_t debug_gpio_port = GPIOA;
	static const uint16_t debug_gpio_pins = GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	gpio_mode_set(debug_gpio_port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, debug_gpio_pins);
	gpio_output_options_set(debug_gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, debug_gpio_pins);
	gpio_bit_reset(debug_gpio_port, debug_gpio_pins);
}

static void uart_config(void)
{
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}

static void systick_config(void)
{
	systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);
	const uint32_t ahb_frequency = rcu_clock_freq_get(CK_AHB);
	SysTick_Config(ahb_frequency / 100);
}

static void timer_config(void)
{
    timer_parameter_struct timer_initpara;
    timer_oc_parameter_struct timer_ocintpara;

    timer_deinit(TIMER_INSTANCE);

    // TIMER7 configuration (250 kHz)
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 799;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER_INSTANCE, &timer_initpara);

    // CH0/2 in PWM1 mode
	timer_channel_output_struct_para_init(&timer_ocintpara);
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER_INSTANCE, TIMER_CH_0, &timer_ocintpara);
    //timer_channel_output_config(TIMER_INSTANCE, TIMER_CH_1, &timer_ocintpara);
    timer_channel_output_config(TIMER_INSTANCE, TIMER_CH_2, &timer_ocintpara);
    //timer_channel_output_config(TIMER_INSTANCE, TIMER_CH_3, &timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER_INSTANCE, TIMER_CH_0,  49); // for period updating DMA
    //timer_channel_output_pulse_value_config(TIMER_INSTANCE, TIMER_CH_1,  99); // for debugging
    timer_channel_output_pulse_value_config(TIMER_INSTANCE, TIMER_CH_2, 149); // for debugging
    //timer_channel_output_pulse_value_config(TIMER_INSTANCE, TIMER_CH_3, 249); // for debugging
    timer_channel_output_mode_config(TIMER_INSTANCE, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    //timer_channel_output_mode_config(TIMER_INSTANCE, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_mode_config(TIMER_INSTANCE, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    //timer_channel_output_mode_config(TIMER_INSTANCE, TIMER_CH_3, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER_INSTANCE, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
    //timer_channel_output_shadow_config(TIMER_INSTANCE, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);
    timer_channel_output_shadow_config(TIMER_INSTANCE, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);
    //timer_channel_output_shadow_config(TIMER_INSTANCE, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

    // TIMER7 primary output enable
    timer_primary_output_config(TIMER_INSTANCE, ENABLE);

    // TIMER7 update DMA request enable
    timer_dma_enable(TIMER_INSTANCE, TIMER_DMA_CH0D);
    //timer_dma_enable(TIMER_INSTANCE, TIMER_DMA_UPD);

    // auto-reload preload enable
    //timer_auto_reload_shadow_enable(TIMER_INSTANCE);
}

static void dma_config(void)
{
	// time period DMA_channel configuration
	dma_single_data_parameter_struct dma_init_struct;

	// if using timer indirect register access from DMA...
#if   (TIMER_WRITE_TESTCASE == DMA_WRITE_CAR_INDIRECT)
	timer_dma_transfer_config(TIMER_INSTANCE, TIMER_DMACFG_DMATA_CAR, TIMER_DMACFG_DMATC_1TRANSFER);
#elif (TIMER_WRITE_TESTCASE == DMA_WRITE_CH2CV_INDIRECT)
	timer_dma_transfer_config(TIMER_INSTANCE, TIMER_DMACFG_DMATA_CH2CV, TIMER_DMACFG_DMATC_1TRANSFER);
#elif (TIMER_WRITE_TESTCASE == DMA_WRITE_PSC_INDIRECT)
	timer_dma_transfer_config(TIMER_INSTANCE, TIMER_DMACFG_DMATA_PSC, TIMER_DMACFG_DMATC_1TRANSFER);
#endif // TIMER_WRITE_TESTCASE

	// configure timer period DMA
	dma_deinit(TIMER_DMA_INSTANCE, TIMER_DMA_CHANNEL);

#if   (TIMER_WRITE_TESTCASE == DMA_WRITE_CAR)
	dma_init_struct.periph_addr         = (uint32_t)&TIMER_CAR(TIMER_INSTANCE);
#elif (TIMER_WRITE_TESTCASE == DMA_WRITE_CH2CV)
	dma_init_struct.periph_addr         = (uint32_t)&TIMER_CH2CV(TIMER_INSTANCE);
#elif (TIMER_WRITE_TESTCASE == DMA_WRITE_PSC)
	dma_init_struct.periph_addr         = (uint32_t)&TIMER_PSC(TIMER_INSTANCE);
#elif (TIMER_WRITE_TESTCASE == DMA_WRITE_CAR_INDIRECT) \
   || (TIMER_WRITE_TESTCASE == DMA_WRITE_CH2CV_INDIRECT) \
   || (TIMER_WRITE_TESTCASE == DMA_WRITE_PSC_INDIRECT)
	dma_init_struct.periph_addr         = (uint32_t)&TIMER_DMATB(TIMER_INSTANCE);
#endif // TIMER_WRITE_TESTCASE

	dma_init_struct.memory0_addr        = (uint32_t)period_buffer;
	dma_init_struct.direction           = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_32BIT;
	dma_init_struct.priority            = DMA_PRIORITY_HIGH;
	dma_init_struct.number              = sizeof(period_buffer)/sizeof(uint32_t);
	dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.circular_mode       = DMA_CIRCULAR_MODE_ENABLE;
	dma_single_data_mode_init(TIMER_DMA_INSTANCE, TIMER_DMA_CHANNEL, &dma_init_struct);
	dma_channel_subperipheral_select(TIMER_DMA_INSTANCE, TIMER_DMA_CHANNEL, TIMER_DMA_SUBPER);
}

int _write(int file, char *ptr, int len)
{
	(void)file;
    for (int i = 0; i < len; i++)
    {
    	usart_data_transmit(USART0, (uint8_t)*ptr++);
		while (!usart_flag_get(USART0, USART_FLAG_TBE));
    }
    return len;
}
