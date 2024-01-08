/*
 * stm_leds.h
 *
 *  Created on: Jan 7, 2024
 *      Author: tomas
 */

#ifndef INC_STM_LEDS_H_
#define INC_STM_LEDS_H_


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#define DELAYED_OFF_DELAY	  20		///< delay for delayed off mode, the time units corresponds with the "sysTime" params in ledsUpadateLEDState() function
#define FAST_FLASH_DELAY	  100		///< delay for fast flash, the time units corresponds with the "sysTime" params in ledsUpadateLEDState() function
#define SLOW_FLASH_DELAY	  500		///< delay for fast slow, the time units corresponds with the "sysTime" params in ledsUpadateLEDState() function

#define BLINK_DELAY 100
#define SLOW_BLINK_RATIO 25
#define FAST_BLINK_RATIO 5

/*
#define	LEDS_SET_MODE(LED_STRUCT, MODE) \
{ \
	LED_STRUCT.mode = MODE; \
	LED_STRUCT.led_time = SystemTime_u32UpMS; \
}
*/

    /** An enum type.
     *  The LEDs modes
     */
typedef enum {
	LEDS_OFF,				///< LED is pernamently off
	LEDS_ON,				///< LED is pernamently on
	LEDS_DELAYED_OFF,		///< LED is switched off after some time delay, you need to set the time delay into LED_struct.led_time
	LEDS_FAST_FLASH,		///< LED toggles with #FAST_FLASH_DELAY period
	LEDS_SLOW_FLASH,			///< LED toggles with #SLOW_FLASH_DELAY period
	LEDS_FAST_BLINK,
	LEDS_SLOW_BLINK
} LED_mode;


/**
 * Each LED needs own LED_struct
 */
typedef struct LED_struct {
	uint32_t *port_address;		///< base GPIO pointer
	uint32_t channel_mask;		///< mask of GPIO pin
	uint8_t polarity;			///< 1 - LED shines in LOG1
	LED_mode mode;				///< LED_mode enum, state of the LED
	uint32_t led_time;			///< time of next event (toggle, switch off, ...)
	uint8_t blink_state;
} LED_struct;


void ledsUpadateLEDState(LED_struct * actual_led, uint32_t sysTime);


#endif /* INC_STM_LEDS_H_ */
