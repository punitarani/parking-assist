/*
 * init_ram.c
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#include "ram_define.h"

/**
 * Initialize RAM Function
 */
void init_ram()
{
	// Initialize general variables
	time = 0;

	// Initialize LIDAR variables
	lidar_distance_raw 				= 0;
	lidar_distance_buffer_pointer 	= 0;
	lidar_distance_buffer_ready 	= NOT_READY;
	lidar_distance_buffer_sum 		= 0;
	lidar_distance 	= 0;

	// Initialize Position Variables
	distance_car			= 0;	// Distance to car
	distance_parked			= 50;	// Target position
	distance_garage_door	= 0;	// Distance to garage door

	// Switch and Debounce Variables
	sw_level 			= NO_PRESS;
	sw_state 			= NO_PRESS;
	sw_debounce_state 	= DEBOUNCE_IDLE;
	long_press_done 	= NO;
	sw_time_press 		= 0;
	sw_time_release 	= 0;
	sw_on_time 			= 0;
	sw_off_time 		= 0;
}
