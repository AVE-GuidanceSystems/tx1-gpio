// exampleApp.c

#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "jetsonGPIO.h"
#include <stdio.h>
#include "drv2605.h"

DRV2605 drv; //create "drv" object

using namespace std;

int getDistance(int, int);
void printDistance(int, int);

int main(int argc, char *argv[]){

    cout << "Testing the GPIO Pins" << endl;
	
	//Declare GPIO Ports to use
    jetsonGPIO trig = gpio187 ;
    jetsonGPIO echo1 = gpio186 ;
    jetsonGPIO LED1 = gpio219 ;
    
    jetsonGPIO Mtrig = gpio38 ; //motortrigger

    //jetsonGPIO echo2 = gpio5 ;
    //jetsonGPIO LED2 = gpio6 ;
    //jetsonGPIO echo3 = gpio13 ;
    //jetsonGPIO LED3 = gpio19 ;
   
    //Reset Pins
    //~ gpioClose(trig);
    //~ gpioClose(echo1);
    //~ gpioClose(LED1);
    gpioUnexport(trig);
    gpioUnexport(echo1);
    gpioUnexport(LED1);
    gpioUnexport(Mtrig);
    //gpioClose(echo2);
    //gpioClose(LED2);
    //gpioClose(echo3);
    //gpioClose(LED3);
    
    //Make GPIO Avialable for use
    gpioExport(trig);
    gpioExport(echo1);
    gpioExport(LED1);
    gpioExport(Mtrig);
    //gpioExport(echo2);
    //gpioExport(LED2);
    //gpioExport(echo3);
    //gpioExport(LED3);
    
    //~ gpioOpen(trig);
    //~ gpioOpen(echo1);
    //~ gpioOpen(LED1);
    //gpioOpen(echo2);
    //gpioOpen(LED2);
    //gpioOpen(echo3);
    //gpioOpen(LED3);
    
    //Set GPIO Direction
    gpioSetDirection(trig, 1); //set trigger as output
    gpioSetDirection(echo1, 0); //set echo as input
    gpioSetDirection(Mtrig,1)
    //~ gpioSetDirection(echo2, 0); //set echo as input
    //~ gpioSetDirection(echo3, 0); //set echo as input
    gpioSetDirection(LED1, 1); //set LED as output
    //gpioSetDirection(LED2, 1); //set LED as output
    //gpioSetDirection(LED3, 1); //set LED as output
    
	//Set Initial State
	gpioSetValue(trig, 0); //turn pin LOW
	gpioSetValue(Utrig, 0);
	gpioSetValue(LED, 0);
	gpioSetValue(echo, 0);
    
    cout << "Setup Complete" << endl;
    int count = 0;
    //unsigned char effect = 47;
    while(1){
		cout << "Starting: " << count << endl;
		count++;
		int distance1 = getDistance(trig, echo1);
		cout << distance1 << endl;
		if ((distance1 >= 300) || (distance1 <= 20)){
			gpioSetValue(LED1, 0); //Turn off led when out of range
			gpioSetValue(Mtrig, 0);//deactivate trigger
		}
		else{
			gpioSetValue(LED1, 1); //Turn on when in range
			
			//activate motor
			cout << "Effect #" << (int)effect << endl;
			//activate motor trigger
			gpioSetValue(Mtrig, 1);
			drv.setWaveform(0,47);	//Run Effect #47
			drv.setWaveform(1,0);	//End waveform
		
			drv.go(); //play effect
			//usleep(300000); //wait for 3/10 of a sec
		}
		printDistance(1, distance1);
		usleep(10);

		//int distance2 = getDistance(trig, echo2);
		//if ((distance2 >= 300) || (distance2 <= 20)){
			//gpioSetValue(LED2, 0); //Turn off led when out of range
		//}
		//else
			//gpioSetValue(LED2, 1); //Turn on when in range
		
		//printDistance(2, distance2);
		//usleep(10);

		//int distance3 = getDistance(trig, echo3);
		//if ((distance3 >= 300) || (distance3 <= 20)){
			//gpioSetValue(LED3, 0); //Turn off led when out of range
		//}
		//else
			//gpioSetValue(LED3, 1); //Turn on when in range
		
		//printDistance(3, distance3);
		//usleep(10);
	}    
}

int getDistance(int trigPin, int echoPin){
	gpioSetValue(trigPin, 0);
	usleep(100);
	clock_t start;
	clock_t end;
	
	gpioSetValue(trigPin, 1); //activate Trigger
	//usleep(12);
	start = clock(); 
	//gpioSetValue(trigPin, 0); //deactivate trigger
	
	unsigned int tempValue = 0;
	cout << "Grabbing start of pulse..." << endl;
	while (tempValue == 0){
			gpioGetValue(echoPin, &tempValue); //continue reading if no edge detected
			//cout << "stuck" << endl;
	}
	start = clock(); //calculates current time --start of pulse

	gpioSetValue(trigPin, 0); //deactivate trigger
	
	cout << "Grabbing end of pulse..." << endl;
	while (tempValue == 1){
			gpioGetValue(echoPin, &tempValue); //continue reading if no edge detected
	}
	end = clock();//calculate current time --end of pulse
	usleep(10000);	
	double pulseTime = (end - start); 
	int distance = pulseTime / 58;
	//cout << pulseTime << "  Dist:  " << distance << endl;
	
	return distance;
}

void printDistance(int id, int dist){
	cout << "Ultrasonic Sensor # "<< id << endl;
	if ((dist >= 300) || (dist <= 20)){
		cout << "Out of Range" << endl;
	}
	else{
		for(int i = 0; i <= dist; i++){
			cout << "-";
		}
		cout << dist << "cm" << endl;
	}
}
