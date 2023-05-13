#include "systick.h"
//initializing systic timer

void SysTick_Init(void){
NVIC_ST_CTRL_R = 0; // 1) disable SysTick during setup
NVIC_ST_RELOAD_R = 0x00FFFFFF; // 2) maximum reload value
NVIC_ST_CURRENT_R = 0; // 3) any write to CURRENT clears it
NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}
void SysTick_Wait(void){
NVIC_ST_RELOAD_R = 16000-1; // number of counts
NVIC_ST_CURRENT_R = 0; // any value written to CURRENT clears
while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for flag
}}


void SysTick_Waitu(void){			// wait 1 micro sec and used in lcd
NVIC_ST_RELOAD_R = 16-1; // number of counts
NVIC_ST_CURRENT_R = 0; // any value written to CURRENT clears
while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for flag
}}


void SysTick_Wait1ms(uint32_t delay)// wait 1ms
{
        uint32_t i;
	for(i=0;i<delay;i++)
	{
	  SysTick_Wait();

	}
}


void SysTick_Wait1us(uint32_t delay)		//wait 1 micro sec
{
        uint32_t i;
	for(i=0;i<delay;i++)
	{
	SysTick_Waitu();
	}
}
