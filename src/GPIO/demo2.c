#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"

void RCC_Configuration_Demo2()
{
	// RCC Configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}

void GPIO_Configuration_Demo2()
{
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructureA.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
	// GPIO Configuration
	// LED3 (Green): GPIO_Pin_13, LED4 (Red): GPIO_Pin_14
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void Interrupts_Configuration_Demo2(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Connect EXTI Line 0 to the button GPIO Pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0);
	
	/* Configure the EXTI line to generate an interrupt when the button is
	 * pressed. The button pin is high when pressed, so it needs to trigger
	 * when rising from low to high. */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

//__attribute__((naked))
void EXTI0_IRQHandler(void)
{
    GPIOG->ODR = 0x0000FFFF;
    GPIOG->ODR = 0x00000000;
	//if(EXTI_GetFlagStatus(EXTI_Line0) != RESET)
	//{
    //__asm__("push {r7, lr}");
    //__asm__("add r7, sp, #0");
    EXTI_ClearITPendingBit(EXTI_Line0);
    //__asm__("pop {r7, pc}");

	//}
}

void demo()
{
	RCC_Configuration_Demo2();
	GPIO_Configuration_Demo2();
	Interrupts_Configuration_Demo2();

	// Demo Code: UserButton to toggle LED3, LED4 is still flashing
	while(1)
	{
        int i = 1000000;
        while(i--);
//        for(int i = 0;i < 1000000;++i){
//            __asm__("nop");
//        }
	}

}
