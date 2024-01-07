/*
 * stm_leds.c
 *
 *  Created on: Jan 7, 2024
 *      Author: tomas
 */


#include "stm_leds.h"


void ledsUpadateLEDState(LED_struct * actual_led, uint32_t sysTime)
{

	switch (actual_led->mode)
	{

		case LEDS_OFF:
			if(actual_led->polarity)
			{
				*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
			}
			else
			{
				*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
			}
			break;

		case LEDS_ON:
			if(actual_led->polarity)
			{
				*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
			}
			else
			{
				*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
			}
			break;

		case LEDS_DELAYED_OFF:
			if(actual_led->polarity)
			{
				*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
			}
			else
			{
				*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
			}

			if((sysTime - actual_led->led_time) > DELAYED_OFF_DELAY)
			{
				actual_led->mode = LEDS_OFF;
			}
			break;

		case LEDS_FAST_FLASH:
			if((sysTime - actual_led->led_time) > FAST_FLASH_DELAY)
			{
				*(actual_led->port_address+5) ^= actual_led->channel_mask; // GPIOx_ODR
				actual_led->led_time = sysTime;
			}
			break;

		case LEDS_SLOW_FLASH:
			if((sysTime - actual_led->led_time) > SLOW_FLASH_DELAY)
			{
				*(actual_led->port_address+5) ^= actual_led->channel_mask; // GPIOx_ODR
				actual_led->led_time = sysTime;
			}
			break;

		case LEDS_FAST_BLINK:
			if((sysTime - actual_led->led_time) > BLINK_DELAY)//timer
			{
				actual_led->led_time = sysTime;


				if(actual_led-> blink_state > FAST_BLINK_RATIO) actual_led-> blink_state = 0;
				else actual_led-> blink_state++;

				if((actual_led-> blink_state == 0)) //led on
				{

					if(actual_led->polarity)
					{
						*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
					}
					else
					{
						*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
					}
				}
				else //led off
				{

					if(actual_led->polarity)
					{
						*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
					}
					else
					{
						*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
					}
				}
			}

		case LEDS_SLOW_BLINK:
					if((sysTime - actual_led->led_time) > BLINK_DELAY)//timer
					{
						actual_led->led_time = sysTime;


						if(actual_led-> blink_state > SLOW_BLINK_RATIO) actual_led-> blink_state = 0;
						else actual_led-> blink_state++;

						if((actual_led-> blink_state == 0)) //led on
						{

							if(actual_led->polarity)
							{
								*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
							}
							else
							{
								*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
							}
						}
						else //led off
						{

							if(actual_led->polarity)
							{
								*(actual_led->port_address+6) = actual_led->channel_mask; // GPIOx_BSRR
							}
							else
							{
								*(actual_led->port_address+6) = (actual_led->channel_mask<<16); // GPIOx_BSRR
							}
						}

					}

			break;

		default:
			break;
	}

	return;

}


