/*
 * app__superloop.h
 *
 *  Created on: 12. 3. 2022
 *      Author: tomas
 */

#ifndef INC_APP__MAINLOOP_H_
#define INC_APP__MAINLOOP_H_


#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//#include "lwip.h"

#include "app_communication.h"
#include "app_gpio_function.h"
#include "app_main_function.h"
#include "app_usart_process.h"
#include "app_spi_function_DAC.h"
#include "app_error.h"
#include "app_udp.h"

void application_main();


#endif /* INC_APP__MAINLOOP_H_ */
