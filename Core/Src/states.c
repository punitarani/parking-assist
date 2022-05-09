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


// Declarations
void system_set();


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
    read_lidar();
    time = HAL_GetTick();

    switch (system_state)
    {
        case STATE_IDLE:
            break;

        case STATE_SET:
            debounce();
            system_set();

            if (sw_state == LONG_PRESS)
            {
                system_state = STATE_MAIN;
                sw_long_press_done = YES;
            }
            break;

        case STATE_MAIN:
        default:
            debounce();
            assist();

            if (sw_state == LONG_PRESS)
            {
                system_state = STATE_SET;
                sw_long_press_done = YES;
            }
            break;
    }
}


void system_set()
{
    switch (system_set_state)
    {
        // Wait 3s for user to step away
        // Blink all three LEDs
        case SET_STATE_WAIT:
            switch (set_state_cntr1)
            {
                // Initialize
                case 0:
                    set_state_cntr1     = 1;
                    set_state_cntr2     = 0;
                    set_state_timer1    = time;
                    break;

                    // ON All LEDs
                case 1:
                    if (time - set_state_timer1 > 500) {
                        set_state_cntr1     = 2;
                        set_state_timer1    = time;

                        control_led(RED, 	ON);
                        control_led(YELLOW, ON);
                        control_led(GREEN, 	ON);
                    }
                    break;

                    // OFF All LEDs
                case 2:
                    if (time - set_state_timer1 > 500) {
                        control_led(RED, OFF);
                        control_led(YELLOW, OFF);
                        control_led(GREEN, OFF);

                        set_state_cntr2 ++;
                        set_state_timer1    = time;

                        // Repeat ON All LEDs if not done 3 times yet
                        (set_state_cntr2 == 3) ? (set_state_cntr1 = 3): (set_state_cntr1 = 1);
                    }
                    break;

                    // Done
                case 3:
                default:
                    // Reset Variables
                    set_state_cntr1     = 0;
                    set_state_cntr2     = 0;
                    set_state_timer1    = 0;

                    // Go to STATE_MAIN
                    system_set_state = SET_STATE_SET;
                    break;
            }
            break;


        // Collect 256 data samples from lidar and average
        // LEDs will blink one by one
        case SET_STATE_SET:
            // Initialize
            if (distance_set_buffer_pointer == 0) {
                distance_set_buffer_sum     = 0;
                distance_set_buffer_average = 0;
            }

            // Update distance set buffer
            if (distance_set_buffer_pointer < (DISTANCE_SET_BUFFER_SIZE - 1)) {
                // Update distance set buffer
                distance_set_buffer[distance_set_buffer_pointer] = lidar_distance;

                // Update distance set buffer sum
                distance_set_buffer_sum += lidar_distance;

                // Increment pointer
                distance_set_buffer_pointer ++;
            }

            else
            {
                // Reset pointer
                distance_set_buffer_pointer = 0;

                // Calculate average distance
                distance_set_buffer_average = distance_set_buffer_sum / DISTANCE_SET_BUFFER_SIZE;

                // Update distance_parked
                distance_parked = distance_set_buffer_average;

                // End LED control loop
                set_state_cntr1 = 5;
            }


            // LED control loop
            switch (set_state_cntr1)
            {
                // Initialize
                case 0:
                    set_state_cntr1     = 1;
                    set_state_cntr2     = 0;
                    set_state_timer1    = time;
                    break;

                // RED LED
                case 1:
                    toggle_one_led(RED);
                    if (time - set_state_timer1 > 200) {
                        set_state_cntr1     = 2;
                        set_state_timer1    = time;
                    }
                    break;

                // YELLOW LED
                case 2:
                    toggle_one_led(YELLOW);
                    if (time - set_state_timer1 > 200) {
                        set_state_cntr1     = 3;
                        set_state_timer1    = time;
                    }
                    break;

                // GREEN LED
                case 3:
                    toggle_one_led(GREEN);
                    if (time - set_state_timer1 > 200) {
                        set_state_cntr1     = 4;
                        set_state_timer1    = time;
                    }
                    break;

                // YELLOW LED reverse
                case 4:
                    toggle_one_led(YELLOW);
                    if (time - set_state_timer1 > 200) {
                        set_state_cntr1     = 1;
                        set_state_timer1    = time;
                    }
                    break;

                // Done
                case 5:
                default:
                    // Reset Variables
                    set_state_cntr1     = 0;
                    set_state_cntr2     = 0;
                    set_state_timer1    = 0;

                    system_set_state = SET_STATE_DONE;
                    break;
            }

            break;


        // Blink green LED for 1s when done
        case SET_STATE_DONE:
        default:
            switch (set_state_cntr1)
            {
                // Initialize
                case 0:
                    set_state_cntr1     = 1;
                    set_state_cntr2     = 0;
                    set_state_timer1    = time;
                    break;

                // ON All LEDs
                case 1:
                    if (time - set_state_timer1 > 500) {
                        set_state_cntr1     = 2;
                        set_state_timer1    = time;

                        toggle_one_led(GREEN);
                    }
                    break;

                // OFF All LEDs
                case 2:
                    if (time - set_state_timer1 > 500) {
                        control_led(GREEN, OFF);

                        set_state_cntr2 ++;
                        set_state_timer1    = time;

                        // Repeat ON All LEDs if not done 3 times yet
                        (set_state_cntr2 == 3) ? (set_state_cntr1 = 3): (set_state_cntr1 = 1);
                    }
                    break;

                // Done
                case 3:
                default:
                    // Reset Variables
                    set_state_cntr1     = 0;
                    set_state_cntr2     = 0;
                    set_state_timer1    = 0;

                    // Go to STATE_MAIN
                    system_state = STATE_MAIN;
                    break;
            }
            break;
    }
}
