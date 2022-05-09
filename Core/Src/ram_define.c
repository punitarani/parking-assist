/*
 * ram_define.c
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#include "ram_define.h"

// General Variables
uint32_t time;

// LIDAR Variables
uint8_t UART1_RX_BUFFER[UART1_RX_BUFFER_SIZE] = {0};
uint16_t lidar_distance_buffer[LIDAR_DIST_BUFFER_SIZE] = {0};

uint16_t lidar_distance_raw;
uint16_t lidar_distance_buffer_pointer;
uint16_t lidar_distance_buffer_ready;
uint32_t lidar_distance_buffer_sum;
uint16_t lidar_distance;


// Distance Variables
uint16_t distance_car;
uint16_t distance_parked;
uint16_t distance_garage_door;


// Switch and Debounce Variables
uint8_t sw_level;
uint8_t sw_state;
uint8_t sw_debounce_state;
uint8_t sw_long_press_done;
uint32_t sw_time_press;
uint32_t sw_time_release;
uint32_t sw_on_time;
uint32_t sw_off_time;

// State Variables
uint8_t system_state;

// Assist Variables
uint8_t assist_cntr1;
uint8_t assist_cntr2;
uint32_t assist_timer;

// System SET variables
uint8_t system_set_state;
uint8_t distance_set_buffer[DISTANCE_SET_BUFFER_SIZE] = {0};
uint8_t distance_set_buffer_pointer;
uint16_t distance_set_buffer_sum;
uint8_t distance_set_buffer_average;
uint8_t set_state_cntr1;
uint8_t set_state_cntr2;
uint32_t set_state_timer1;
