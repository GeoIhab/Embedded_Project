#ifndef MY_LCD
#define MY_LCD
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "systick.h"

 
void LCD_init(void); /*initialize LCD*/
void LCD_displayString(const char *Str);/*Display always string (func to display string)*/
void LCD_sendCommand(uint8_t command);/*Sending commands to LCD*/
void LCD_displayCharacter(uint8_t data);/*Display character to be used in displaying string*/
void LCD_Clear(void);/*Clear the LCD*/
void LCD_displayfloat(float data);/* Converting the float to string because LCD displays string*/
#endif
