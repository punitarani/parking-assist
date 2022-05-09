/*
 * debounce.c
 *
 *  Created on: May 8, 2022
 *      Author: punit
 */

#include "debounce.h"
#include "main.h"
#include "ram_define.h"

/**
 * Switch Debouncing Function
 */
void debounce()
{
	// Read switch
	sw_level = HAL_GPIO_ReadPin(SWITCH_GPIO_Port, SWITCH_Pin);

	// Get time
	time = HAL_GetTick();
	sw_on_time = time - sw_time_press;
	sw_off_time = time - sw_time_release;



	// DEBOUNCE
	switch(sw_debounce_state)
	{
		// Continue Debouncing
		case DEBOUNCE_PRESS:
			// Switch is still pressed
			if (sw_level == PRESS)
			{
				// Check if switch held for short press time
				if (sw_on_time >= DEBOUNCE_SHORT_TIME)
				{
					sw_debounce_state = DEBOUNCE_RELEASE;
				}

				// Reset
				sw_time_release = 0;
				sw_off_time = 0;
			}

			// Switch is not pressed
			else
			{
				if (sw_time_release == 0)
				{
					sw_time_release = time;
				}

				else if (sw_off_time >= DEBOUNCE_RELEASE_TIME)
				{
					sw_debounce_state = DEBOUNCE_IDLE;

					// Reset
					sw_time_release = 0;
					sw_off_time = 0;
				}
			}
			break;

		// Terminate Debouncing
		case DEBOUNCE_RELEASE:
			// Switch is still pressed
			if (sw_level == PRESS)
			{
				if (sw_on_time >= DEBOUNCE_LONG_TIME)
				{
					// Check if Long Press has been acknowledged
					if (sw_long_press_done == YES)
					{
						sw_state = NO_PRESS;

						// Continue to wait for release
					}

					// If not: assert Long Press
					else
					{
						sw_state = LONG_PRESS;
						sw_long_press_done = NO;
					}
				}
			}

			// Switch is not pressed
			else
			{
				if (sw_time_release == 0)
				{
					sw_time_release = time;
				}

				// Check if switch held for short press time
				if ((sw_on_time >= DEBOUNCE_SHORT_TIME) && (sw_on_time <= DEBOUNCE_LONG_TIME))
				{
					sw_state = SHORT_PRESS;

					// Reset
					sw_debounce_state 	= DEBOUNCE_IDLE;
					sw_time_press 		= 0;
					sw_time_release 	= 0;
					sw_on_time 			= 0;
					sw_off_time 		= 0;
				}

				else if (sw_on_time >= DEBOUNCE_LONG_TIME)
				{
					// Reset
					sw_long_press_done 	= NO;
					sw_debounce_state 	= DEBOUNCE_IDLE;
					sw_time_press 		= 0;
					sw_time_release 	= 0;
					sw_on_time 			= 0;
					sw_off_time 		= 0;
				}

				// Check if switch release is more than the release time
				if (sw_off_time >= DEBOUNCE_RELEASE_TIME)
				{
					sw_state = NO_PRESS;

					// Reset
					sw_debounce_state 	= DEBOUNCE_IDLE;
					sw_time_press 		= 0;
					sw_time_release 	= 0;
					sw_on_time 			= 0;
					sw_off_time 		= 0;
				}
			}
			break;

		// Idle Debouncing
		case DEBOUNCE_IDLE:
		default:
			sw_state = NO_PRESS;

			// Begin Debouncing
			if (sw_level == PRESS)
			{
				sw_debounce_state 	= DEBOUNCE_PRESS;
				sw_time_press 		= time;
			}

			// Remain in Idle State
			else
			{
				sw_debounce_state 	= DEBOUNCE_IDLE;
				sw_time_press 		= 0;
				sw_time_release 	= 0;
				sw_on_time 			= 0;
				sw_off_time 		= 0;
			}
			break;
	}
}
