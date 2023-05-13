#include "UART.h"
#include "LCD.h"
#include "systick.h"
#include "GPS.h"
#include "GPIO.h"
#include "Global_vars.h"




int main()

{
volatile	float flag;			//flag for measurment errors
	volatile float dist=0;//variable to save distance after calling function that calculate distance between two points
	float lat_arr[3];/*array to save latitude */
	float long_arr[3];/*array to save current Longitude*/
volatile	float displacement;
    int counter=0;/*variable used as acounter to increased every cycle of distance calc (every second) */
	
	UART7_INIT();	/*initialize the uart of the gps*/	
	GPIO_initPORTF(); // initialize port f for leds
	SysTick_Init(); //initialize systick for delays
	LCD_init(); /*initialize the gpio port of the lcd currently B*/
	
		
while(1){
	
		GPS_read(); //reads the log from the GPS
		GPS_format();	//formats the data from the log
		
		long_arr[counter] = currentLong;
		lat_arr[counter] = currentLat;
		if(counter!=0)
			{
				flag=GPS_getDistance(long_arr[counter-1],lat_arr[counter-1],long_arr[counter],lat_arr[counter]);	//stores the distance between the current and previous readings
				if(	flag<1000){			//failsafe for when the gps returns incorrect coordinates
				if(speed>0.5){			//failsafe for when the user is not moving
				dist += flag;
				LCD_Clear();/*clear screen to not overwrite on screen*/
				LCD_displayfloat(dist);	/*display distance on lcd*/
				}
			}
		}
		displacement = GPS_getDistance(long_arr[counter], lat_arr[counter],finalLong,finalLat);
				
				
				 
				if(displacement>=100)
					{ 		
					led_off(GPIO_ALL_LEDS);
			    led_on(0x02);/*turn on red led when distance >100*/   
			    }
				
				if(displacement>=0 && displacement<5)
				{
					led_off(GPIO_ALL_LEDS);
					led_on(0x08);
												/*turn on green led when 0<distance <1*/
				}	
				if(displacement>=5 && displacement<100)
				{
					led_off(GPIO_ALL_LEDS);
					led_on(0x02);
					led_on(0x08); //turn on yellow led when 1<distance<100
				}	
		    
			if(counter==2){				//reset the counter of the array
				counter=0;
				long_arr[0] = long_arr[2];
				lat_arr[0] = lat_arr[2];
			}
			counter++;/*increase counter by 1*/

		
	}
	
}