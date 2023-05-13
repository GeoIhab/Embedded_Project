#include "LCD.h"


void LCD_init(void){				//intializes lcd and port B
 SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};/*waite to activate*/ 
  GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
  GPIO_PORTB_PCTL_R   &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
  GPIO_PORTB_DIR_R    |= 0xFF;         /* Configure PORTB as output pin */
  GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
  GPIO_PORTB_DEN_R   |= 0xFF;         /* Enable Digital I/O onPORTB */
  GPIO_PORTB_DATA_R   &= 0x0;         /* Clear data in PORT B */
		
SysTick_Wait1ms(20);//delay 20ms
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1ms(5);//DELAY 5mS
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1us(100);//DELAY 40uS
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1us(40);//DELAY 40uS
LCD_sendCommand(0x20); /* use 4-bit data mode */
SysTick_Wait1us(40);//DELAY 40uS
 LCD_sendCommand(0X28); /* Select 4-bit Mode of LCD */
 LCD_sendCommand(0X06); /* clear whatever is written on display */
 LCD_sendCommand(0X01); /* shift cursor right */
 LCD_sendCommand(0X0F);  /* Enable Display and cursor blinking */
 }
 
 
 
 void LCD_sendCommand(uint8_t command){									// send command to LCD
GPIO_PORTB_DATA_R &=0xFC;    /*Instruction Mode RS=0 /write data to LCD so RW=0 */
/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | (command & 0xF0));
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40);//delay 40us 
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
 GPIO_PORTB_DATA_R = ((	GPIO_PORTB_DATA_R & 0x0F) | ((command<< 4)&0xF0));/*write data*/
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
 SysTick_Wait1us(40);
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
if(command<4)
SysTick_Wait1ms(2);//delay 2ms	 
else 
SysTick_Wait1us(40);//delay 40us
}
 



void LCD_displayString(const char *Str) //send data as string
{
  uint8_t i = 0;
 while(Str[i] != '\0')
{
	LCD_displayCharacter(Str[i]);
		i++;
 }} 


 void LCD_displayCharacter(uint8_t data)		//send data as char
 {
 GPIO_PORTB_DATA_R |=0x01; /* Instruction Mode RS=1 /write data to LCD so RW=0/ENABLE=0 */
GPIO_PORTB_DATA_R = ( GPIO_PORTB_DATA_R & 0x0F) | (data& 0xF0);
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40); 	 
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
GPIO_PORTB_DATA_R = ((	GPIO_PORTB_DATA_R & 0x0F) | ((data<< 4)&0xF0));/*write data*/
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40); 	
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
SysTick_Wait1us(40); 	 
}




 void LCD_Clear()		// clear the lcd values to write new one
{
LCD_sendCommand(1);//clear diplay
LCD_sendCommand(0x80); /* LCD cursor location */
SysTick_Wait1ms(500);
}	

		


void LCD_displayfloat(float data) 	// Function discription :function used to convert float numbers to string and diplay on the lcd 		
{char str[7];
 int i;
 i=0;
 sprintf(str,"%f",data);//used to convert flaot to string
 LCD_sendCommand(1); /* clear display */
 LCD_sendCommand(0x80); /* LCD cursor location */
		
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
		SysTick_Wait1ms(500);//delay 500ms
}
