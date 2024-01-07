/*
 * app_leds.c
 *
 *  Created on: Jan 7, 2024
 *      Author: tomas
 */

#include "app_leds.h"
#include "main.h"

LEDs_struct LEDs_GREEN_LED1, LEDs_GREEN_LED2, LEDs_RED_LED;


void app_leds_init(void)
{
	/* init of LEDs structures */
	LEDs_GREEN_LED1.port_address = (uint32_t*) LED_0_GPIO_Port;
	LEDs_GREEN_LED1.channel_mask = LED_0_Pin;
	LEDs_GREEN_LED1.polarity = 0;
	LEDs_GREEN_LED1.led_time = 0;
	LEDs_GREEN_LED1.mode = LEDS_OFF;

	LEDs_GREEN_LED2.port_address = (uint32_t*) LED_1_GPIO_Port;
	LEDs_GREEN_LED2.channel_mask = LED_1_Pin;
	LEDs_GREEN_LED2.polarity = 0;
	LEDs_GREEN_LED2.led_time = 0;
	LEDs_GREEN_LED2.mode = LEDS_OFF;

	LEDs_RED_LED.port_address = (uint32_t*) LED_2_GPIO_Port;
	LEDs_RED_LED.channel_mask = LED_2_Pin;
	LEDs_RED_LED.polarity = 0;
	LEDs_RED_LED.led_time = 0;
	LEDs_RED_LED. blink_state = 0;
	LEDs_RED_LED.mode = LEDS_OFF;



}
