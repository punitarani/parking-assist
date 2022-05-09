/*
 * assist.c
 *
 *  Created on: May 8, 2022
 *      Author: punit
 */

#include "assist.h"
#include "led.h"
#include "main.h"


/**
 * Main control algorithm for parking assist
 */
void assist()
{
	if (lidar_distance >= (distance_parked + SLOW_BUFFER))
	{
		toggle_one_led(GREEN);
	}

	else if (lidar_distance >= (distance_parked + STOP_BUFFER))
	{
		toggle_one_led(YELLOW);
	}

	else if (lidar_distance >= (distance_parked - STOP_BUFFER))
	{
		toggle_one_led(RED);
	}

	else
	{
		switch (assist_cntr1)
		{
			// Initialize
			case 0:
				assist_cntr1 = 1;
                assist_cntr2 = 0;
				assist_timer = time;
				break;

			// ON ALL LEDs
			case 1:
                if (time - assist_timer >= 375)
                {
                	control_led(RED, ON);
                    control_led(YELLOW, ON);
                    control_led(GREEN, ON);

                    assist_cntr1 = 2;
                    assist_timer = time;
                }
				break;

			// OFF ALL LEDs
			case 2:
                if (time - assist_timer >= 375)
                {
                    control_led(RED, OFF);
                    control_led(YELLOW, OFF);
                    control_led(GREEN, OFF);

                    assist_timer = time;
                    assist_cntr2 ++;

                    (assist_cntr2 == 10) ? (assist_cntr1 = 3) : (assist_cntr1 = 1);
                }
				break;

			// Stop Blinking
			case 3:
			default:
                toggle_one_led(RED);

                // Reset
                assist_cntr1 = 0;
                assist_cntr2 = 0;
                assist_timer = 0;
				break;
		}
	}
}
