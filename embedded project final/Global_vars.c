#include "Global_vars.h"

 volatile char GPS[80];
 char GPS_logname[]="$GPRMC,";
 char GPS_formated[12][20];
 char*token;
 float currentLong   ;
 float	currentLat  ;
 float speed;
 float finalLat=3003.85572; 
 float finalLong=3116.78872;
 const double EARTH_RADIUS = 6371000;
 const double PI=3.14159265359;