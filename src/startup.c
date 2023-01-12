
#define WEAK __attribute__ ((weak))
 
void WEAK Reset_Handler(void);
void WEAK NMI_Handler(void);
void WEAK HardFault_Handler(void);
void WEAK MemManage_Handler(void);
void WEAK BusFault_Handler(void);
void WEAK UsageFault_Handler(void);
void WEAK SVC_Handler(void);
void WEAK DebugMon_Handler(void);
void WEAK PendSV_Handler(void);
void WEAK SysTick_Handler(void);

void WEAK WWDGT_IRQHandler(void);
void WEAK LVD_IRQHandler(void);
void WEAK TAMPER_STAMP_IRQHandler(void);
void WEAK RTC_WKUP_IRQHandler(void);
void WEAK FMC_IRQHandler(void);
void WEAK RCU_CTC_IRQHandler(void);
void WEAK EXTI0_IRQHandler(void);
void WEAK EXTI1_IRQHandler(void);
void WEAK EXTI2_IRQHandler(void);
void WEAK EXTI3_IRQHandler(void);
void WEAK EXTI4_IRQHandler(void);
void WEAK DMA0_Channel0_IRQHandler(void);
void WEAK DMA0_Channel1_IRQHandler(void);
void WEAK DMA0_Channel2_IRQHandler(void);
void WEAK DMA0_Channel3_IRQHandler(void);
void WEAK DMA0_Channel4_IRQHandler(void);
void WEAK DMA0_Channel5_IRQHandler(void);
void WEAK DMA0_Channel6_IRQHandler(void);
void WEAK ADC_IRQHandler(void);
void WEAK CAN0_TX_IRQHandler(void);
void WEAK CAN0_RX0_IRQHandler(void);
void WEAK CAN0_RX1_IRQHandler(void);
void WEAK CAN0_EWMC_IRQHandler(void);
void WEAK EXTI5_9_IRQHandler(void);
void WEAK TIMER0_BRK_TIMER8_IRQHandler(void);
void WEAK TIMER0_UP_TIMER9_IRQHandler(void);
void WEAK TIMER0_TRG_CMT_TIMER10_IRQHandler(void);
void WEAK TIMER0_Channel_IRQHandler(void);
void WEAK TIMER1_IRQHandler(void);
void WEAK TIMER2_IRQHandler(void);
void WEAK TIMER3_IRQHandler(void);
void WEAK I2C0_EV_IRQHandler(void);
void WEAK I2C0_ER_IRQHandler(void);
void WEAK I2C1_EV_IRQHandler(void);
void WEAK I2C1_ER_IRQHandler(void);
void WEAK SPI0_IRQHandler(void);
void WEAK SPI1_IRQHandler(void);
void WEAK USART0_IRQHandler(void);
void WEAK USART1_IRQHandler(void);
void WEAK USART2_IRQHandler(void);
void WEAK EXTI10_15_IRQHandler(void);
void WEAK RTC_Alarm_IRQHandler(void);
void WEAK USBFS_WKUP_IRQHandler(void);
void WEAK TIMER7_BRK_TIMER11_IRQHandler(void);
void WEAK TIMER7_UP_TIMER12_IRQHandler(void);
void WEAK TIMER7_TRG_CMT_TIMER13_IRQHandler(void);
void WEAK TIMER7_Channel_IRQHandler(void);
void WEAK DMA0_Channel7_IRQHandler(void);
void WEAK EXMC_IRQHandler(void);
void WEAK SDIO_IRQHandler(void);
void WEAK TIMER4_IRQHandler(void);
void WEAK SPI2_IRQHandler(void);
void WEAK UART3_IRQHandler(void);
void WEAK UART4_IRQHandler(void);
void WEAK TIMER5_DAC_IRQHandler(void);
void WEAK TIMER6_IRQHandler(void);
void WEAK DMA1_Channel0_IRQHandler(void);
void WEAK DMA1_Channel1_IRQHandler(void);
void WEAK DMA1_Channel2_IRQHandler(void);
void WEAK DMA1_Channel3_IRQHandler(void);
void WEAK DMA1_Channel4_IRQHandler(void);
void WEAK ENET_IRQHandler(void);
void WEAK ENET_WKUP_IRQHandler(void);
void WEAK CAN1_TX_IRQHandler(void);
void WEAK CAN1_RX0_IRQHandler(void);
void WEAK CAN1_RX1_IRQHandler(void);
void WEAK CAN1_EWMC_IRQHandler(void);
void WEAK USBFS_IRQHandler(void);
void WEAK DMA1_Channel5_IRQHandler(void);
void WEAK DMA1_Channel6_IRQHandler(void);
void WEAK DMA1_Channel7_IRQHandler(void);
void WEAK USART5_IRQHandler(void);
void WEAK I2C2_EV_IRQHandler(void);
void WEAK I2C2_ER_IRQHandler(void);
void WEAK USBHS_EP1_Out_IRQHandler(void);
void WEAK USBHS_EP1_In_IRQHandler(void);
void WEAK USBHS_WKUP_IRQHandler(void);
void WEAK USBHS_IRQHandler(void);
void WEAK DCI_IRQHandler(void);
void WEAK TRNG_IRQHandler(void);
void WEAK FPU_IRQHandler(void);
void WEAK UART6_IRQHandler(void);
void WEAK UART7_IRQHandler(void);
void WEAK SPI3_IRQHandler(void);
void WEAK SPI4_IRQHandler(void);
void WEAK SPI5_IRQHandler(void);
void WEAK TLI_IRQHandler(void);
void WEAK TLI_ER_IRQHandler(void);
void WEAK IPA_IRQHandler (void);

 // Exported constants which defined in linker script.
//extern unsigned long __etext;
extern unsigned long _sidata;	// start addr for the init values of the .data section. 
extern unsigned long _sdata;	
extern unsigned long _edata;
//extern unsigned long __data_start__;	// start addr for the .data section.
//extern unsigned long __data_end__;		// end addr for the .data section.
extern unsigned long __bss_start__;		// start addr for the .bss section.
extern unsigned long __bss_end__;			// end addr for the .bss section.
//extern unsigned long __stack;					// init value for the stack pointer.
extern unsigned long _estack;

// Function prototypes
void __attribute__((section(".text_init"))) Reset_Handler(void);
extern int main(void);    
extern int SystemInit(void);                                                                                                                                                                                                                                          
extern void __libc_init_array(void);

__attribute__ ((section(".isr_vector")))
__attribute__ ((used))
void (* const g_pfnVectors[])(void) = {
  // The initial stack pointer                                                                                                                                                                                                          
//	(void (*)(void))((unsigned long) 0x02100000),    //TODO                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	(void (*)(void))((unsigned long)&_estack),  
    Reset_Handler,                      //Reset Handler
    NMI_Handler,                        //NMI Handler
    HardFault_Handler,                  //Hard Fault Handler
    MemManage_Handler,                  //MPU Fault Handler
    BusFault_Handler,                   //Bus Fault Handler
    UsageFault_Handler,                 //Usage Fault Handler
    0,                                  //Reserved
    0,                                  //Reserved
    0,                                  //Reserved
    0,                                  //Reserved
    SVC_Handler,                        //SVCall Handler
    DebugMon_Handler,                   //Debug Monitor Handler
    0,                                  //Reserved
    PendSV_Handler,                     //PendSV Handler
    SysTick_Handler,                    //SysTick Handler

    /* external interrupts handler */
    WWDGT_IRQHandler,                   // 16:Window Watchdog Timer
    LVD_IRQHandler,                     // 17:LVD through EXTI Line detect
    TAMPER_STAMP_IRQHandler,            // 18:Tamper and TimeStamp through EXTI Line detect
    RTC_WKUP_IRQHandler,                // 19:RTC Wakeup through EXTI Line
    FMC_IRQHandler,                     // 20:FMC
    RCU_CTC_IRQHandler,                 // 21:RCU and CTC
    EXTI0_IRQHandler,                   // 22:EXTI Line 0
    EXTI1_IRQHandler,                   // 23:EXTI Line 1
    EXTI2_IRQHandler,                   // 24:EXTI Line 2
    EXTI3_IRQHandler,                   // 25:EXTI Line 3
    EXTI4_IRQHandler,                   // 26:EXTI Line 4
    DMA0_Channel0_IRQHandler,           // 27:DMA0 Channel0
    DMA0_Channel1_IRQHandler,           // 28:DMA0 Channel1
    DMA0_Channel2_IRQHandler,           // 29:DMA0 Channel2
    DMA0_Channel3_IRQHandler,           // 30:DMA0 Channel3
    DMA0_Channel4_IRQHandler,           // 31:DMA0 Channel4
    DMA0_Channel5_IRQHandler,           // 32:DMA0 Channel5
    DMA0_Channel6_IRQHandler,           // 33:DMA0 Channel6
    ADC_IRQHandler,                     // 34:ADC
    CAN0_TX_IRQHandler,                 // 35:CAN0 TX
    CAN0_RX0_IRQHandler,                // 36:CAN0 RX0
    CAN0_RX1_IRQHandler,                // 37:CAN0 RX1
    CAN0_EWMC_IRQHandler,               // 38:CAN0 EWMC
    EXTI5_9_IRQHandler,                 // 39:EXTI5 to EXTI9
    TIMER0_BRK_TIMER8_IRQHandler,       // 40:TIMER0 Break and TIMER8
    TIMER0_UP_TIMER9_IRQHandler,        // 41:TIMER0 Update and TIMER9
    TIMER0_TRG_CMT_TIMER10_IRQHandler,  // 42:TIMER0 Trigger and Commutation and TIMER10
    TIMER0_Channel_IRQHandler,          // 43:TIMER0 Capture Compare
    TIMER1_IRQHandler,                  // 44:TIMER1
    TIMER2_IRQHandler,                  // 45:TIMER2
    TIMER3_IRQHandler,                  // 46:TIMER3
    I2C0_EV_IRQHandler,                 // 47:I2C0 Event
    I2C0_ER_IRQHandler,                 // 48:I2C0 Error
    I2C1_EV_IRQHandler,                 // 49:I2C1 Event
    I2C1_ER_IRQHandler,                 // 50:I2C1 Error
    SPI0_IRQHandler,                    // 51:SPI0
    SPI1_IRQHandler,                    // 52:SPI1
    USART0_IRQHandler,                  // 53:USART0
    USART1_IRQHandler,                  // 54:USART1
    USART2_IRQHandler,                  // 55:USART2
    EXTI10_15_IRQHandler,               // 56:EXTI10 to EXTI15
    RTC_Alarm_IRQHandler,               // 57:RTC Alarm
    USBFS_WKUP_IRQHandler,              // 58:USBFS Wakeup
    TIMER7_BRK_TIMER11_IRQHandler,      // 59:TIMER7 Break and TIMER11
    TIMER7_UP_TIMER12_IRQHandler,       // 60:TIMER7 Update and TIMER12
    TIMER7_TRG_CMT_TIMER13_IRQHandler,  // 61:TIMER7 Trigger and Commutation and TIMER13
    TIMER7_Channel_IRQHandler,          // 62:TIMER7 Channel Capture Compare
    DMA0_Channel7_IRQHandler,           // 63:DMA0 Channel7
    EXMC_IRQHandler,                    // 64:EXMC
    SDIO_IRQHandler,                    // 65:SDIO
    TIMER4_IRQHandler,                  // 66:TIMER4
    SPI2_IRQHandler,                    // 67:SPI2
    UART3_IRQHandler,                   // 68:UART3
    UART4_IRQHandler,                   // 69:UART4
    TIMER5_DAC_IRQHandler,              // 70:TIMER5 and DAC0 DAC1 Underrun error
    TIMER6_IRQHandler,                  // 71:TIMER6
    DMA1_Channel0_IRQHandler,           // 72:DMA1 Channel0
    DMA1_Channel1_IRQHandler,           // 73:DMA1 Channel1
    DMA1_Channel2_IRQHandler,           // 74:DMA1 Channel2
    DMA1_Channel3_IRQHandler,           // 75:DMA1 Channel3
    DMA1_Channel4_IRQHandler,           // 76:DMA1 Channel4
    ENET_IRQHandler,                    // 77:Ethernet
    ENET_WKUP_IRQHandler,               // 78:Ethernet Wakeup through EXTI Line
    CAN1_TX_IRQHandler,                 // 79:CAN1 TX
    CAN1_RX0_IRQHandler,                // 80:CAN1 RX0
    CAN1_RX1_IRQHandler,                // 81:CAN1 RX1
    CAN1_EWMC_IRQHandler,               // 82:CAN1 EWMC
    USBFS_IRQHandler,                   // 83:USBFS
    DMA1_Channel5_IRQHandler,           // 84:DMA1 Channel5
    DMA1_Channel6_IRQHandler,           // 85:DMA1 Channel6
    DMA1_Channel7_IRQHandler,           // 86:DMA1 Channel7
    USART5_IRQHandler,                  // 87:USART5
    I2C2_EV_IRQHandler,                 // 88:I2C2 Event
    I2C2_ER_IRQHandler,                 // 89:I2C2 Error
    USBHS_EP1_Out_IRQHandler,           // 90:USBHS Endpoint 1 Out 
    USBHS_EP1_In_IRQHandler,            // 91:USBHS Endpoint 1 in
    USBHS_WKUP_IRQHandler,              // 92:USBHS Wakeup through EXTI Line
    USBHS_IRQHandler,                   // 93:USBHS
    DCI_IRQHandler,                     // 94:DCI
    0,                                  // 95:Reserved
    TRNG_IRQHandler,                    // 96:TRNG
    FPU_IRQHandler,                     // 97:FPU
    UART6_IRQHandler,                   // 98:UART6
    UART7_IRQHandler,                   // 99:UART7
    SPI3_IRQHandler,                    // 100:SPI3
    SPI4_IRQHandler,                    // 101:SPI4
    SPI5_IRQHandler,                    // 102:SPI5
    0,                                  // 103:Reserved
    TLI_IRQHandler,                     // 104:TLI
    TLI_ER_IRQHandler,                  // 105:TLI Error
    IPA_IRQHandler                      // 106:IPA
};   

#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler

#pragma weak WWDGT_IRQHandler = Default_Handler
#pragma weak LVD_IRQHandler = Default_Handler
#pragma weak TAMPER_STAMP_IRQHandler = Default_Handler
#pragma weak RTC_WKUP_IRQHandler = Default_Handler
#pragma weak FMC_IRQHandler = Default_Handler
#pragma weak RCU_CTC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA0_Channel0_IRQHandler = Default_Handler
#pragma weak DMA0_Channel1_IRQHandler = Default_Handler
#pragma weak DMA0_Channel2_IRQHandler = Default_Handler
#pragma weak DMA0_Channel3_IRQHandler = Default_Handler
#pragma weak DMA0_Channel4_IRQHandler = Default_Handler
#pragma weak DMA0_Channel5_IRQHandler = Default_Handler
#pragma weak DMA0_Channel6_IRQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak CAN0_TX_IRQHandler = Default_Handler
#pragma weak CAN0_RX0_IRQHandler = Default_Handler
#pragma weak CAN0_RX1_IRQHandler = Default_Handler
#pragma weak CAN0_EWMC_IRQHandler = Default_Handler
#pragma weak EXTI5_9_IRQHandler = Default_Handler
#pragma weak TIMER0_BRK_TIMER8_IRQHandler = Default_Handler
#pragma weak TIMER0_UP_TIMER9_IRQHandler = Default_Handler
#pragma weak TIMER0_TRG_CMT_TIMER10_IRQHandler = Default_Handler
#pragma weak TIMER0_Channel_IRQHandler = Default_Handler
#pragma weak TIMER1_IRQHandler = Default_Handler
#pragma weak TIMER2_IRQHandler = Default_Handler
#pragma weak TIMER3_IRQHandler = Default_Handler
#pragma weak I2C0_EV_IRQHandler = Default_Handler
#pragma weak I2C0_ER_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak SPI0_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak USART0_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak EXTI10_15_IRQHandler = Default_Handler
#pragma weak RTC_Alarm_IRQHandler = Default_Handler
#pragma weak USBFS_WKUP_IRQHandler = Default_Handler
#pragma weak TIMER7_BRK_TIMER11_IRQHandler = Default_Handler
#pragma weak TIMER7_UP_TIMER12_IRQHandler = Default_Handler
#pragma weak TIMER7_TRG_CMT_TIMER13_IRQHandler = Default_Handler
#pragma weak TIMER7_Channel_IRQHandler = Default_Handler
#pragma weak DMA0_Channel7_IRQHandler = Default_Handler
#pragma weak EXMC_IRQHandler = Default_Handler
#pragma weak SDIO_IRQHandler = Default_Handler
#pragma weak TIMER4_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak UART3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak TIMER5_DAC_IRQHandler = Default_Handler
#pragma weak TIMER6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel0_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak ENET_IRQHandler = Default_Handler
#pragma weak ENET_WKUP_IRQHandler = Default_Handler
#pragma weak CAN1_TX_IRQHandler = Default_Handler
#pragma weak CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_EWMC_IRQHandler = Default_Handler
#pragma weak USBFS_IRQHandler = Default_Handler
#pragma weak DMA1_Channel5_IRQHandler = Default_Handler
#pragma weak DMA1_Channel6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel7_IRQHandler = Default_Handler
#pragma weak USART5_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak USBHS_EP1_Out_IRQHandler = Default_Handler
#pragma weak USBHS_EP1_In_IRQHandler = Default_Handler
#pragma weak USBHS_WKUP_IRQHandler = Default_Handler
#pragma weak USBHS_IRQHandler = Default_Handler
#pragma weak DCI_IRQHandler = Default_Handler
#pragma weak TRNG_IRQHandler = Default_Handler
#pragma weak FPU_IRQHandler = Default_Handler
#pragma weak UART6_IRQHandler = Default_Handler
#pragma weak UART7_IRQHandler = Default_Handler
#pragma weak SPI3_IRQHandler = Default_Handler
#pragma weak SPI4_IRQHandler = Default_Handler
#pragma weak SPI5_IRQHandler = Default_Handler
#pragma weak TLI_IRQHandler = Default_Handler
#pragma weak TLI_ER_IRQHandler = Default_Handler
#pragma weak IPA_IRQHandler  = Default_Handler


/* This is the code that gets called when the processor receives an unexpected
	interrupt.  This simply enters an infinite loop, preserving the system state
	for examination by a debugger. */
void Default_Handler(void)
{
	while (1); // Go into an infinite loop.
}


/* This is the code that gets called when the processor first starts execution
	following a reset event.  Only the absolutely necessary set is performed,
	after which the application supplied main() routine is called. */
void __attribute__ ((naked)) __attribute__((section(".text_init"))) Reset_Handler(void)
{
	unsigned long *pulSrc, *pulDest;    
	// Zero fill the bss segment.
	for(pulDest = &__bss_start__; pulDest < &__bss_end__; )
		*(pulDest++) = 0;

    pulDest = &_sdata; 
    pulSrc = &_sidata;
    while (pulDest < &_edata)
    {
        *pulDest++ = *pulSrc++;
    }

//	clock_update();

//	VTOR_update((unsigned*)g_pfnVectors);
    SystemInit();
    __libc_init_array();
//	setup();

	// Call the application's entry point.
	main();
	// Go to infinite loop
	Default_Handler();
}
