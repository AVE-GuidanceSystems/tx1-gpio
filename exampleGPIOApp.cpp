// exampleApp.c

#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "jetsonGPIO.h"
using namespace std;

int getDistance(int, int);
void printDistance(int, int);

int main(int argc, char *argv[]){

    cout << "Testing the GPIO Pins" << endl;
	
	//Declare GPIO Ports to use
    jetsonGPIO trig = gpio4 ;
    jetsonGPIO echo1 = gpio17 ;
    jetsonGPIO LED1 = gpio27 ;
    jetsonGPIO echo2 = gpio5 ;
    jetsonGPIO LED2 = gpio6 ;
    jetsonGPIO echo3 = gpio13 ;
    jetsonGPIO LED3 = gpio19 ;
   
    //Reset Pins
    gpioClose(gpio4);
    gpioClose(gpio17);
    gpioClose(gpio27);
    gpioClose(gpio5);
    gpioClose(gpio6);
    gpioClose(gpio13);
    gpioClose(gpio19);
    
    gpioOpen(gpio4);
    gpioOpen(gpio17);
    gpioOpen(gpio27);
    gpioOpen(gpio5);
    gpioOpen(gpio6);
    gpioOpen(gpio13);
    gpioOpen(gpio19);
    
    //Make GPIO Avialable for use
    gpioExport(trig);
    gpioExport(echo1);
    gpioExport(gpio27);
    gpioExport(echo2);
    gpioExport(gpio6);
    gpioExport(echo3);
    gpioExport(gpio19);
    
    gpioSetDirection(trig, 1); //set trigger as output
    gpioSetDirection(echo1, 0); //set echo as input
    gpioSetDirection(echo2, 0); //set echo as input
    gpioSetDirection(echo3, 0); //set echo as input
    gpioSetDirection(LED1, 1); //set LED as output
    gpioSetDirection(LED2, 1); //set LED as output
    gpioSetDirection(LED3, 1); //set LED as output
    
    while(1){
		int distance1 = getDistance(trig, echo1);
		if ((distance1 >= 300) || (distance1 <= 20)){
			gpioSetValue(LED1, 0); //Turn off led when out of range
		}
		else
			gpioSetValue(LED1, 1); //Turn on when in range
		
		printDistance(1, distance1);
		usleep(10);

		int distance2 = getDistance(trig, echo2);
		if ((distance2 >= 300) || (distance2 <= 20)){
			gpioSetValue(LED2, 0); //Turn off led when out of range
		}
		else
			gpioSetValue(LED2, 1); //Turn on when in range
		
		printDistance(2, distance2);
		usleep(10);

		int distance3 = getDistance(trig, echo3);
		if ((distance3 >= 300) || (distance3 <= 20)){
			gpioSetValue(LED3, 0); //Turn off led when out of range
		}
		else
			gpioSetValue(LED3, 1); //Turn on when in range
		
		printDistance(3, distance3);
		usleep(10);
	}
    
    
}
int getDistance(int trigPin, int echoPin){
	clock_t start;
	clock_t end;
	
	gpioSetValue(trigPin, 1); //activate Trigger
	usleep(10);
	start = clock(); 
	//gpioSetValue(trigPin, 0); //deactivate trigger
	
	unsigned int tempValue = 0;
	while (tempValue == 0){
			gpioGetValue(echoPin, &tempValue); //continue reading if no edge detected
	}
	gpioSetValue(trigPin, 0); //deactivate trigger
	
	start = clock(); //calculates current time --start of pulse
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
	cout << "Ultrasonic Sensor #" << id << endl;
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
