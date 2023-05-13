#include "tm4c123gh6pm.h"
#include "UART.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Global_vars.h"



void GPS_read();
void GPS_format();
float toDegree(float angle);
float toRad(float angle);
float GPS_getDistance(float currentLong, float currentLat , float destLong,float destLat);
