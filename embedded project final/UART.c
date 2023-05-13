#include "UART.h"



void UART7_INIT(){								//intializes Uart7 
 SYSCTL_RCGCUART_R |= 0x80; //turns on clock for uart 7
 SYSCTL_RCGCGPIO_R |= 0x10; //turns on clock for port E
	

UART7_CTL_R &= ~ 0x01; //turns off uart 7
	//sets the baudrate to 9600
	UART7_IBRD_R = 104;  
	UART7_FBRD_R = 11;
UART7_LCRH_R = 0x70  ;//enables fifo and sets the word length to 8
UART7_CTL_R =0x301 ;//turns on uart 7 ,Rx,Tx
  
GPIO_PORTE_AFSEL_R |= 0x3;//enables alternate function on pins 0,1
GPIO_PORTE_PCTL_R |= 0x11; //configure uart7 for pins 0,1
GPIO_PORTE_DEN_R |= 0x03;//enables digital data on pins0,1
GPIO_PORTE_AMSEL_R &= ~0x03;  //disables analog data on pins0,1
}

char Uart7_receive(void)	//recieves a character from uart7
{
while ((UART7_FR_R & 0x10) != 0)
;
return (char)(UART7_DR_R & 0xFF);
}



