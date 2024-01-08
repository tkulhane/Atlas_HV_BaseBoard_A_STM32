/*
 * app_leds.h
 *
 *  Created on: Jan 7, 2024
 *      Author: tomas
 */

#ifndef INC_APP_LEDS_H_
#define INC_APP_LEDS_H_

#include "stm_leds.h"


typedef LED_struct LEDs_struct;

extern LEDs_struct LEDs_GREEN_LED1, LEDs_GREEN_LED2, LEDs_RED_LED;

void app_leds_init(void);
void app_leds_drive();

#endif /* INC_APP_LEDS_H_ */
