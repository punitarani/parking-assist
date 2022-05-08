/*
 * led.c
 *
 *  Created on: May 8, 2022
 *      Author: punit
 */

#include "led.h"
#include "main.h"


/**
 * Control one LED
 *
 * @param led LED (RED, GREEN, YELLOW)
 * @param on_off State (ON or OFF)
 */
void control_led(uint8_t led, uint8_t on_off)
{
	// Pair on_off to LED_ON/OFF
	(on_off == ON) ? (on_off = LED_ON) : (on_off = LED_OFF);

	// Control LED
	switch (led)
	{
	case RED:
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, 	LED_RED_Pin, 	on_off);
		break;

	case YELLOW:
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, on_off);
		break;

	case GREEN:
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, 	LED_GREEN_Pin, 	on_off);
		break;

    default:
        break;
    }
}

/**
 * Toggle one LED ON, others OFF
 *
 * @param led LED to turn ON (RED, GREEN, YELLOW)
 */
void toggle_one_led(uint8_t led)
{
	control_led(RED, 	(led == RED) 	? ON : OFF);
	control_led(YELLOW, (led == YELLOW) ? ON : OFF);
	control_led(GREEN, 	(led == GREEN) 	? ON : OFF);
}

