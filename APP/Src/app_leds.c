/*
 * app_leds.c
 *
 *  Created on: Jan 7, 2024
 *      Author: tomas
 */

#include "app_leds.h"
#include "main.h"

#include "app_error.h"
#include "app_main_function.h"

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


	  //leds
	  ledsUpadateLEDState(&LEDs_GREEN_LED1, HAL_GetTick());
	  ledsUpadateLEDState(&LEDs_GREEN_LED2, HAL_GetTick());
	  ledsUpadateLEDState(&LEDs_RED_LED, HAL_GetTick());
}


void app_leds_drive()
{

	//connect led
	if(_AppConnected)
	{
		 LEDs_GREEN_LED1.mode = LEDS_FAST_FLASH;
	}
	else
	{
		 LEDs_GREEN_LED1.mode = LEDS_SLOW_BLINK;
	}




	 //channels enable led
	 if(ChannelsStatus[0].enable || ChannelsStatus[1].enable || ChannelsStatus[2].enable)
	 {
		 LEDs_GREEN_LED2.mode = LEDS_ON;
		  //LEDs_RED_LED.mode = LEDS_FAST_BLINK;
	 }
	 else
	 {
		 LEDs_GREEN_LED2.mode = LEDS_OFF;
		 //LEDs_RED_LED.mode = LEDS_OFF;
	 }


	 //red led
	if(_FoundError_OR)
	{
		LEDs_RED_LED.mode = LEDS_ON;
	}
	else if(ChannelsStatus[0].disableInError || ChannelsStatus[1].disableInError || ChannelsStatus[2].disableInError)
	{
		LEDs_RED_LED.mode = LEDS_ON;
	}
	else if(ChannelsChange[0].restart_request || ChannelsChange[1].restart_request || ChannelsChange[2].restart_request)
	{
		LEDs_RED_LED.mode = LEDS_ON;
	}
	else if(ChannelsStatus[0].enable || ChannelsStatus[1].enable || ChannelsStatus[2].enable)
	{
		LEDs_RED_LED.mode = LEDS_SLOW_BLINK;
	}
	else
	{
		LEDs_RED_LED.mode = LEDS_OFF;
	}



	  //leds update
	  ledsUpadateLEDState(&LEDs_GREEN_LED1, HAL_GetTick());
	  ledsUpadateLEDState(&LEDs_GREEN_LED2, HAL_GetTick());
	  ledsUpadateLEDState(&LEDs_RED_LED, HAL_GetTick());

}
