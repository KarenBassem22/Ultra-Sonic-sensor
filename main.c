/*******************************************************************************
 * File name: fourth_mini_project.c
 * Description: source file for measuring distance using ultrasonic sensor
 * Date: Oct 15, 2021
 * Author: Karen Bassem
 ******************************************************************************/
#include "fourth_mini_project.h"

int main(void){
	LCD_init();
	SREG|=(1<<7);
	ULTRASONIC_init();
	LCD_displayString("Distance=   cm");
	float distance=0;
	while(1){

		distance=Ultrasonic_readDistance();
		LCD_moveCursor(0,9);
		LCD_integerToString(distance);
		if(distance<100){
			LCD_displayCharacter(' ');
		}
		if(distance<10){
			LCD_displayCharacter(' ');
		}
	}
}

