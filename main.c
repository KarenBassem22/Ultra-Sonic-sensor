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
	//_delay_ms(1000);
	//LCD_sendCommand(CLEAR_SCREEN);
	//LCD_moveCursor(2,10);
	//LCD_displayCharacter('k');
	float distance=0;
	while(1){

		Ultrasonic_Trigger();
		if(g_edgeCount==2){
		distance=Ultrasonic_readDistance();
		LCD_moveCursor(0,9);
		LCD_integerToString(distance);
		g_edgeCount=0;
		}
	}
}
