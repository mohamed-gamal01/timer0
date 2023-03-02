/*
 * timer.c
 *
 * Created: 2/26/2023 11:06:12 AM
 * Author : CONNECT
 */ 

#include <avr/io.h>
#include "std_types.h"
#include "bit_math.h"
#include "TIMR0_int.h"
#include "dio.h"

volatile u16 counter=0;
void toggle(void);
int main(void)
{
	u8 time=2;
	TIMER0_void_Init();
	SREG_VoidEnable ();
	counter=put_time(time);
	TIMER0_void_SetTimerReg(0);
	TIMER0_void_SetCompareVal(0);/////////////////*************50************///////////
	TIMER0_void_EnableOVInt();////////////////////badl be TIMER0_void_EnableCTCInt********************/////////////////////
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN4,OUTPUT);
	
	TIMER0_void_SetOVCallBack(toggle);///////////////*******************badl be TIMER0_void_SetCTCCallBack(toggle)*********//////////
	
    
    while (1) 
    {
    }
}

void toggle(void)
{
	static u16 count=0;
	static u16 x;
	x=counter;
	
	if(count==x)
	{
		//dio_vidWriteChannel(DIO_PORTA,DIO_PIN4,STD_HIGH);
		FLIP_BIT(DIO_PORTA_REG,DIO_PIN4);
		count=0;
	}
	count++;
	
}