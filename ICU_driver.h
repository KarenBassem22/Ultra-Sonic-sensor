/*******************************************************************************
 * File name: ICU.h
 * Description: header file for ICU
 * Date: Oct 15, 2021
 * Author: Karen Bassem
 ******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "avr\io.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr\interrupt.h" /* for ICU ISR */

/* enum for defining edge types */
typedef enum{
	FALLING_EDGE,RISING_EDGE
}ICU_edgeType;

/* enum to select the prescaler */
typedef enum{
	NO_CLOCK,NO_PRESCALER,PRESCALER_8,PRESCALER_64,PRESCALER_256,PRESCALER_1024,EXTERNAL_CLK_FALLING_EDGE,EXTERNAL_CLK_RISING_EDGE
}ICU_prescaler;

/* structure for dynamic configuration */
typedef struct{
	ICU_edgeType edge;
	ICU_prescaler prescaler;
}ICU_configType;

#define ICU_PORT_ID  PORTD_ID
#define ICU_PIN_ID   PIN6_ID


/* function prototypes */
void ICU_init(const ICU_configType* config_ptr);
void ICU_setCallBack(void(*a_ptr)(void));
void ICU_clearTimerValue(void);
void ICU_setEdgeDetectionType(const ICU_edgeType a_edgeType);
uint16 ICU_getInputCaptureValue(void);
void ICU_DeInit(void);

#endif /* ICU_H_ */
