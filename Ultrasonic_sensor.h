/*******************************************************************************
 * File name: ULTRASONIC_sensor.h
 * Description: header file for ULTRASONIC sensor using ICU driver
 * Module: ULTRASONIC sensor
 * Author: Karen Bassem
 ******************************************************************************/
#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "gpio.h"
#include "ICU.h"
#include <util\delay.h>

/* define trigger pin */
#define ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID   PIN5_ID

/* global variable */
uint8 g_edgeCount ;

/* function prototypes */
void ULTRASONIC_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_SENSOR_H_ */
