/*
 * main.c
 *
 *  Created on: Jun 28, 2019
 *      Author: Sami
 */
#include <avr/io.h>

#include "../HAL/LCD.h"
#include "../MCAL/UART.h"
#include "../Service_Layer/PLATFORM_TYPES.h"
#include "../Service_Layer/DIO.h"
#include "util/delay.h"


int main()
{
	DDRC=0xFF;
	PORTC=0x00;
	LCD_Init();
	LCD_Clear_Display();
	LCD_Send_String_Row_Column(0,0,"Hello");
	_delay_ms(1000);
	LCD_Clear_Display();

	Uart_init(9600);
	char arr[10];


	while(1)
	{

		UART_recieve_string(arr);

		LCD_Send_String_Row_Column(1,1,arr);


		if(compareString(arr,"startA"))
		{
			SET_BIT(PORTC,PC2); // Enable For Motor A

			SET_BIT(PORTC,PC0);
			CLEAR_BIT(PORTC,PC1);

		}else if (compareString(arr,"startB"))
		{
			SET_BIT(PORTC,PC3); // Enable For Motor B

			SET_BIT(PORTC,PC4);
			CLEAR_BIT(PORTC,PC5);

		}else if (compareString(arr,"stopA"))
		{
			CLEAR_BIT(PORTC,PC2); // Disable For Motor A

		}else if (compareString(arr,"stopB"))
		{
			CLEAR_BIT(PORTC,PC3); // Disable For Motor B
		}else if (compareString(arr,"reverseA"))
		{
			SET_BIT(PORTC,PC2); // Enable For Motor A

			SET_BIT(PORTC,PC1);
			CLEAR_BIT(PORTC,PC0);

		}else if (compareString(arr,"reverseB"))
		{
			SET_BIT(PORTC,PC3); // Enable For Motor B

			SET_BIT(PORTC,PC5);
			CLEAR_BIT(PORTC,PC4);

		}
		_delay_ms(1000);
		LCD_Clear_Display();
	}
	return 0;
}
