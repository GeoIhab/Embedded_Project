#include "Bit_Utilities.h"
#include "tm4c123gh6pm.h"

#define GPIO_RED_LED 2
#define GPIO_GREEN_LED 4
#define GPIO_BLUE_LED 8
#define GPIO_ALL_LEDS 14


void led_off(unsigned char led);
void led_on(unsigned char led);
void GPIO_initPORTF();

