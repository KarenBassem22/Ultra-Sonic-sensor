/*******************************************************************************
 * File name: fourth_mini_project.c
 * Description: source file for measuring distance using ultrasonic sensor
 * Date: Oct 15, 2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "fourth_mini_project.h"

int main(void){
	LCD_init();
	SREG|=(1<<7);        /* enable global interrupt */
	ULTRASONIC_init();
	LCD_displayString("Distance=   cm");
	uint16 distance=0;   /* variable to hold the distance */
	while(1){

		distance=Ultrasonic_readDistance();
		/* to right at a specific place every time */
		LCD_moveCursor(0,9);
		LCD_integerToString(distance);
		/* to display the number correctly when decreasing the distance */
		if(distance<100){
			LCD_displayCharacter(' ');
		}
		if(distance<10){
			LCD_displayCharacter(' ');
		}
	}
}
