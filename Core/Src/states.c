/*
 * states.c
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#include "assist.h"
#include "debounce.h"
#include "init_ram.h"
#include "led.h"
#include "main.h"
#include "tfmini.h"


/**
 * System Initialize Function
 * Main Init
 */
void system_init()
{
    // Initialize Ram
	init_ram();

    // Turn off all LEDs
	control_led(RED, 	OFF);
	control_led(YELLOW, OFF);
	control_led(GREEN, 	OFF);
}


/**
 * System Loop Function
 * Main Loop
 */
void system_loop()
{
	debounce();
	read_lidar();
	assist();
}
