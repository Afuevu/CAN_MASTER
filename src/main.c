#include "FreeRTOS.h"

#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx.h"
#include "task.h"
#include "usart_driver.h"
#include "utils.h"
#include "timer4.h"
#include "uart.h"
#include "adc.h"
#include "timer2.h"
#include "custom_init.h"
#include "can.h"

void vBlinkLedTask(void *pvParameters);
void vBlinkLedTask(void *pvParameters)
{
	(void)pvParameters; // Unused parameter

	while (1)
	{
		GPIOC->ODR ^= (1 << 13);		// Toggle LED
		vTaskDelay(pdMS_TO_TICKS(100)); // Delay 1000 ms (1 second)
	}
}

int main()
{

	sysclock_init();
	systick_init();
	timer4_Init();
	delay_ms(10);
	uart_init();
	delay_ms(5);
	adc_Init();
	timer2_Init();
	custom_Init();
	CAN1_Init();
	delay_ms(500);

	// xTaskCreate(vBlinkLedTask, "BlinkTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	//  vTaskStartScheduler();

	while (1)
	{
		CAN1_Tx();
		GPIOC -> ODR ^= (1 << 13); // Toggle LED
		delay_ms(500);
	}
}

void TIM2_IRQHandler(void)
{
	/* PA0 = ADCVALUE[1];
	 * PA1 = ADCVALUE[2];
	 * PA4 = ADCVALUE[3];
	 * PA5 = ADCVALUE[0];
	 *
	 * */

	TIM2->SR &= ~(1 << 0); // ack the interrupt
}
