/*
 * const_defs.h
 *
 *  Created on: May 7, 2022
 *      Author: punit
 */

#ifndef SRC_CONST_DEFS_H_
#define SRC_CONST_DEFS_H_

// System Defs
#define UART1_RX_BUFFER_SIZE		9			// TF Mini Transmits 9 Bytes
#define UART1_TIMEOUT				100			// UART Timeout: 100ms

// Lidar Defs
#define LIDAR_DIST_BUFFER_SIZE		10			// LIDAR Distance Buffer Size

// Debounce Defs
#define DEBOUNCE_SHORT_TIME			50			// Short Press is 50ms
#define DEBOUNCE_LONG_TIME			2000		// Long Press is 2s
#define DEBOUNCE_RELEASE_TIME		20			// Release time is 20ms
#define DEBOUNCE_IDLE				0			// Debounce Idle State
#define DEBOUNCE_PRESS				1			// Debounce Press State
#define DEBOUNCE_RELEASE			2			// Debounce Release State
#define SHORT_PRESS					1			// Short Press
#define LONG_PRESS					2			// Long Press


// LED Defs
#define LED_ON						0			// LED ON when low
#define LED_OFF						1			// LED OFF when high
#define RED							1			// RED LED
#define YELLOW						2 			// YELLOW LED
#define GREEN						3 			// GREEN LED


// Assist Defs
#define STOP_BUFFER					10          // Stop Buffer distance = distance_parked + 10cm
#define SLOW_BUFFER					100         // Slow Buffer distance = distance_parked + 100cm


// State Defs
#define STATE_IDLE                  0           // Idle State
#define STATE_MAIN                  1           // Main State
#define STATE_SET                   2           // Set State


// System SET defs
#define DISTANCE_SET_BUFFER_SIZE    256		    // SET Buffer Size
#define SET_STATE_WAIT              0           // SET State Wait
#define SET_STATE_SET               1           // SET State Set
#define SET_STATE_DONE              2           // SET State Done


// Word Defs
#define ON							1
#define OFF							0
#define YES							1
#define NO							0
#define TRUE						1
#define FALSE						0
#define READY						1
#define NOT_READY					0
#define PRESS						1
#define NO_PRESS					0

#endif /* SRC_CONST_DEFS_H_ */
