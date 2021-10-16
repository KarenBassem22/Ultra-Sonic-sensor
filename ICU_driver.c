/*******************************************************************************
 * File name: ICU.c
 * Description: source file for ICU
 * Date: Oct 15, 2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "ICU.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR; /* global pointer to function to hold address of call back function */

ISR(TIMER1_CAPT_vect){
	if(g_callBackPtr!=NULL_PTR){  /* check if the global pointer is assigned a function address */
		(*g_callBackPtr)(); /* Call the Call Back function in the application after the edge is detected */
	}
}

/* function to initialize ICU */
void ICU_init(const ICU_configType* config_ptr){
	GPIO_setupPinDirection(ICU_PORT_ID,ICU_PIN_ID,PIN_INPUT);
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);  /* Normal non-PWM mode */
	TCCR1B=(TCCR1B&0xBF)|((config_ptr->edge)<<ICES1); /* To detect rising edge as the first edge */
	TCCR1B=(TCCR1B&0xF8)|(config_ptr->prescaler);     /* prescaler=8 */
	TCNT1=0;                       /* initialize count value with zero */
	ICR1=0;                        /* initialize input capture register value with zero */
	SET_BIT(TIMSK,TICIE1);         /* enable input capture interrupt */
}

/* function to save the address of call back function in a global pointer to function */
void ICU_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}

/* function to clear and start the timer from zero */
void ICU_clearTimerValue(void){
	TCNT1=0;
}

/* Function to choose the edge to be detected */
void ICU_setEdgeDetectionType(const ICU_edgeType a_edgeType){
	TCCR1B=(TCCR1B&0xBF)|(a_edgeType<<ICES1);  /* To detect rising or falling edge as given */
}
/*************************************************************************************************************
 *                     ANOTHER METHOD
 * void ICU_setEdgeDetectionType(const ICU_configType* config_ptr){
 *     TCCR1B=(TCCR1B&0xBF)|((config_ptr->edge)<<ICES1);
 * }
 ************************************************************************************************************/

/* function to read the value of input capture register */
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

/* Function to De-initialise and stop the ICU */
void ICU_DeInit(void){
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;
	CLEAR_BIT(TIMSK,TICIE1);  /* disable input capture interrupt */
}

