/*
 * tfmini.c
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#include "main.h"
#include "tfmini.h"


/**
 * Read LIDAR message from UART1.
 * Parse message to get distance reading.
 */
void read_lidar()
{
	// Get data from TF Mini
	HAL_UART_Receive(&huart1, UART1_RX_BUFFER, UART1_RX_BUFFER_SIZE, UART1_TIMEOUT);

	// Get Distance Bytes
	uint8_t Dist_L = UART1_RX_BUFFER[2];
	uint8_t Dist_H = UART1_RX_BUFFER[3];

	// Combine Dist_H and Dist_L bytes
	if ((Dist_L != 0) | (Dist_H != 0))
	{
        // SLL Dist_H 1 byte and concat with Dist_L
		lidar_distance_raw = (Dist_H << 8) + Dist_L;
	}


	// Update LIDAR buffer with latest reading
	// Cache old value
	uint16_t lidar_distance_buffer_oldest = lidar_distance_buffer[lidar_distance_buffer_pointer];

	// Update Buffer;
	lidar_distance_buffer[lidar_distance_buffer_pointer] = lidar_distance_raw;

	// Increment Buffer Pointer
	lidar_distance_buffer_pointer ++;

	// Buffer Pointer checks
	if (lidar_distance_buffer_pointer == LIDAR_DIST_BUFFER_SIZE)
	{
		// Reset buffer pointer if at the end
		lidar_distance_buffer_pointer = 0;

		// Check if buffer is ready
		if (lidar_distance_buffer_ready == NOT_READY)
		{
			lidar_distance_buffer_ready = READY;
		}
	}

	// Update buffer sum
	lidar_distance_buffer_sum = lidar_distance_buffer_sum - lidar_distance_buffer_oldest + lidar_distance_raw;

	// Calculate buffer average
	lidar_distance = lidar_distance_buffer_sum / LIDAR_DIST_BUFFER_SIZE;
}
