#include "GPS.h"

void GPS_read(){						//reads and stores the GPS log
	//check for correct log
	char recievedChar;

	
	char fillGPScounter = 0;
	char flag=1;
	char i;
	char c;

do{
	flag=1;
	
	for( i=0;i<7;i++){
		c=Uart7_receive();
		if(c!= GPS_logname[i]){
			flag=0;
			break;}
		}
	}while(flag==0);
///////////////////////
	
	//store the log
	do{
		recievedChar= Uart7_receive();
		//UART0_write(recievedChar);
		GPS[fillGPScounter++]=recievedChar;
		//UART0_write(GPS[fillGPScounter-1]);
		
	}while(recievedChar!='*');
}



void GPS_format(){				//formats the GPS log to a 2D array
	char noOfTokenStrings=0;
	token = strtok(GPS , ",");
	do{
		strcpy(GPS_formated[noOfTokenStrings],token);
		token = strtok(NULL,",");
		noOfTokenStrings++;
	}while(token!=NULL);

	if(strcmp(GPS_formated[1],"A")==0){
		if(strcmp(GPS_formated[3],"N")==0)
			currentLat= atof(GPS_formated[2]);
		else 
			currentLat = -atof(GPS_formated[2]);
		if(strcmp(GPS_formated[5],"E")==0)
			currentLong = atof(GPS_formated[4]);
		else 
			currentLong= -atof(GPS_formated[4]);
		speed=atof(GPS_formated[6]);
																		}
}	

float toDegree(float angle){					//converts to degree
	int degree=(int)angle/100;
	float minutes = angle - (float)degree*100;
	return(degree+(minutes/60));
}




float toRad(float angle){				//connverts to radian
	return angle*(PI/180);
}

float GPS_getDistance(float currentLong, float currentLat , float destLong,float destLat){		//returns the distance between the current location and the destination
	float currentLongRad = toRad(toDegree(currentLong)); // 
	float currentLatRad = toRad(toDegree(currentLat));
	float destLongRad = toRad(toDegree(destLong));
	float destLatRad = toRad(toDegree(destLat));
	
	float longDiff = destLongRad - currentLongRad;
	float latDiff = destLatRad - currentLatRad ;
		
	float a = pow(sin(latDiff/2),2)+cos(currentLatRad)*cos(destLatRad)*pow(sin(longDiff/2),2);
	double c = 2*atan2(sqrt(a),sqrt(1-a));
	return 6371000*c;
}









