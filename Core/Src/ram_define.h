/*
 * ram_define.h
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#ifndef SRC_RAM_DEFINE_H_
#define SRC_RAM_DEFINE_H_

#include "const_defs.h"
#include "stdint.h"

// General Variables
uint32_t time;                          // Time Variable to be defined in any function. Holds HAL_GetTick() output.

// LIDAR Variables
uint8_t UART1_RX_BUFFER[UART1_RX_BUFFER_SIZE];              // Buffer to hold UART1 Receive values.
uint16_t lidar_distance_buffer[LIDAR_DIST_BUFFER_SIZE];     // Buffer to hold LIDAR distance values.

uint16_t lidar_distance_raw;            // Latest LIDAR distance value.
uint16_t lidar_distance_buffer_pointer; // Pointer holding the index of the first value in LIDAR distance buffer.
uint16_t lidar_distance_buffer_ready;   // Boolean asserting when buffer is full and ready.
uint32_t lidar_distance_buffer_sum;     // Sum  of values in LIDAR distance buffer.
uint16_t lidar_distance;                // LIDAR distance. Average of buffer values.

// Position Variables
uint16_t distance_car;                  // Distance of Car. Live reading from LIDAR.
uint16_t distance_parked;               // Ideal parked distance of car.
uint16_t distance_garage_door;          // Distance to garage door.


// Switch and Debounce Variables
uint8_t sw_level;					    // Switch GPIO Level        (PRESS / NO_PRESS)
uint8_t sw_state;					    // Switch debounced state	(NO_PRESS / SHORT_PRESS / LONG_PRESS)
uint8_t sw_debounce_state;			    // Switch debounce state	(DEBOUNCE_IDLE / DEBOUNCE_PRESS / DEBOUNCE_RELEASE)
uint8_t long_press_done;			    // Long press acknowledged	(YES / NO)
uint32_t sw_time_press;                 // Switch press time
uint32_t sw_time_release;               // Switch release time
uint32_t sw_on_time;                    // Time - sw_time_press
uint32_t sw_off_time;                   // Time - sw_release_time

#endif /* SRC_RAM_DEFINE_H_ */
