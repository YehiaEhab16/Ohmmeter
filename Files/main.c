/*
 * main.c
 *
 *  Created on: Sep 22, 2020
 *      Author: yehia
 */

#include "STD_TYPES.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum);

void main(void)
{
	u16 Local_u16Analog, Local_u16Voltage, Local_u16Resistance;

	PORT_voidInit();
	ADC_voidInit();

	CLCD_voidInit();

	while(1)
	{
		ADC_u8StartConversionSynch(0,&Local_u16Analog);
		Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

		Local_u16Resistance = (5000UL * 10000UL / (u32)Local_u16Voltage) - 10000UL;

		CLCD_voidGotoXY(0,0);
		CLCD_voidSendString("Res:");
		CLCD_voidSendNumber(Local_u16Resistance);
		CLCD_voidSendString("Ohm");

		_delay_ms(50);
	}
}

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum)
{
	u16 Local_u16OutputNumber = (((f32)(Copy_u16OutputMaximum - Copy_u16OutputMinimum) / (f32)(Copy_u16InputMaximum - Copy_u16InputMinimum))*(f32)(Copy_u16InputNumber - Copy_u16InputMinimum)) + Copy_u16OutputMinimum;

	return Local_u16OutputNumber;
}
