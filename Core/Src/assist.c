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
	if (lidar_distance >= (distance_parked * GO_MULTIPLIER))
	{
		toggle_one_led(GREEN);
	}

	else if (lidar_distance >= (distance_parked * SLOW_MULTIPLIER))
	{
		toggle_one_led(YELLOW);
	}

	else
	{
		toggle_one_led(RED);
	}
}
