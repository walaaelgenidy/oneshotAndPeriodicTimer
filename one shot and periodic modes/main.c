#include "tm4c123gh6pm.h"
#include <stdio.h>

void SystemInit(void)
{
	SCB->CPACR |= 0x00F00000;
}
void delayMs(int n );
void timer0A_delayMs(int time);


	
 //--------------------------------------------------------------------------
	
	//This program demonstrates the use of TimerA of Timer0 block to do a delay of the
  //multiple of milliseconds. Because 16-bit mode is used, it will only work up to 4 ms.
	//toggling a led using one shot mode....16-bit mode
	
	int main (void)
	{
		SYSCTL->RCGCGPIO |=0X20; //ENABLE CLK FOR PORTF
		GPIOF->DEN = 0X0E;       //SET PINS AS DIGITAL (PIN 1.2.3)
		GPIOF->DIR = 0X0E;       //SET DIRECTION AS OUTPUT
		
		while(1)
		{
			
		GPIOF->DATA = 2; //TURN ON THE LED
		timer0A_delayMs(100);//Timer A msec delay
		GPIOF->DATA =0; //TURN OFF THE LED 
		timer0A_delayMs(100); 
		
		}
	}
/*		
		
		while(1)
		{
			
		GPIOF->DATA = 2; //TURN ON THE LED
		timer0A_delayMs(2);//Timer A msec delay
		GPIOF->DATA =0; //TURN OFF THE LED 
		delayMs(3);
		
	}
}
	
//-----delay using one-shot mode------

void timer0A_delayMs(int time)
{
   SYSCTL->RCGCTIMER |=1;	//ENABLE CLK OF TIMER
	 TIMER0->CTL =0;       //DISABLE TIMER WHILE BEING CONFIGURED
	 TIMER0->CFG =0X04;    //16-BIT MODE SELECTION
	 TIMER0->TAMR =0X01;   //SELECT ONE SHOT MODE AND DOWN COUNTER 
	 TIMER0->TAILR = 16000 * time - 1; // SETTING INTERVAL LOAD VALUE REGISTER
   TIMER0->ICR = 0;     //CLEAR FLAG 
   TIMER0->CTL |=0X01;   //ENABLE TIMER 	
	
   while ((TIMER0->RIS & 0x1) == 0) ;
	// wait for TimerA timeout flag to set
}
*/

//-------- delay using periodic mode --------

void timer0A_delayMs(int time)
{
 int i;
	
 SYSCTL->RCGCTIMER |= 1;          // enable clock to Timer Block 0 
 TIMER0->CTL = 0;               // disable Timer before initialization 
 TIMER0->CFG = 0X00;           // 32-bit option 
 TIMER0->TAMR = 0x02;         // periodic mode and down-counter 
 TIMER0->TAILR = 16000 - 1;  // Timer A interval load value register 
 TIMER0->ICR = 0x1;         // clear the TimerA timeout flag
 TIMER0->CTL |= 0x01;      // enable Timer A after initialization 
	//TIMER1->TAPR = 250 - 1;  // TimerA Prescaler 16MHz/250=64000Hz to create one secnd delay
 for(i = 0; i < time; i++)
{
while ((TIMER0->RIS & 0x1) == 0) ;// wait for TimerA timeout flag 
TIMER0->ICR = 0x1;
 }
}
//--------------------------------------------------
 /*
void delayMs(int n)
  {
int i, j;
 for(i = 0 ; i < n; i++)
 for(j = 0; j < 3180; j++)
	{}
*/
