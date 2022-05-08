/*
 * led.h
 *
 *  Created on: May 8, 2022
 *      Author: punit
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include "stdint.h"

/**
 * Control one LED
 *
 * @param led LED (RED, GREEN, YELLOW)
 * @param on_off State (ON or OFF)
 */
void control_led(uint8_t led, uint8_t on_off);


/**
 * Toggle one LED ON, others OFF
 *
 * @param led LED to turn ON (RED, GREEN, YELLOW)
 */
void toggle_one_led(uint8_t led);

#endif /* SRC_LED_H_ */
