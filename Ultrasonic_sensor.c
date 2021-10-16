/*******************************************************************************
 * File name: ULTRASONIC_sensor.c
 * Description: source file for ULTRASONIC sensor using ICU driver
 * Module: ULTRASONIC sensor
 * Author: Karen Bassem
 ******************************************************************************/
#include "ULTRASONIC_sensor.h"

/* global variables */
uint8 g_edgeCount = 0;
uint16 g_highTime = 0;

/* function to initialize ULTRASONIC sensor */
void ULTRASONIC_init(void){
	ICU_configType Config_Ptr={RISING_EDGE,PRESCALER_8};
	ICU_init(&Config_Ptr); /* Pass the structure to initialize ICU */
	/*
	 * void (*a_funPtr)(void);
	 * a_funPtr=Ultrasonic_edgeProcessing;
	 * ICU_setCallBack(a_funPtr);
	 */
	ICU_setCallBack(Ultrasonic_edgeProcessing);  /* pass the call back function */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT); /* set trigger pin as output */
}

/* function to send trigger pulse to ultra-sonic sensor */
void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH); /* generate trigger pulse */
	_delay_ms(10); /* delay for 10us as required */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);  /* STOP the trigger pulse */
}

/* function to send the trigger pulse and to Start the measurements by the ICU from this moment */
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	uint16 distance_in_cm= (g_highTime*0.017)+2; /* high time (us) * 10^-6 * 340 (m/s) * 100 */
	/* minus two because it can't read a distance less than 2 cm */
	return distance_in_cm;
}

/* function to calculate the high time of the pulse */
void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1){
		/* Clear the timer counter register to start measurements from the first detected rising edge */
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING_EDGE);    /* Detect falling edge */
	}
	else if(g_edgeCount == 2){
		g_highTime = ICU_getInputCaptureValue();   /* to get the High time value */
		ICU_clearTimerValue();  /* added by me */  /* Clear the timer counter register to start measurements again */
		ICU_setEdgeDetectionType(RISING_EDGE);     /* Detect rising edge */
		g_edgeCount=0;
	}
}
