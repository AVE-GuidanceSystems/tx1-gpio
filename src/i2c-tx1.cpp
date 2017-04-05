//============================================================================
// Name        : i2c-tx1.cpp
// Author      : Christian Aguilar
// Version     :
// Copyright   : @2017
// Description : Motor Test Script
//============================================================================

#include <iostream>
#include "drv2605.h"
#include "jetsonGPIO.h"

using namespace std;

//#define MotorTrigger1 = 4;
//#define MotorTrigger2 = 3; //or some gpio number..probably gets replaced soon

DRV2605 drv; //create "drv" object

int main() {

	jetsonGPIO trig = gpio38 ;
	jetsonGPIO UTrig = gpio187;
	jetsonGPIO echo1 = gpio186;
	jetsonGPIO LED1 = gpio219;
	drv.I2CBus = 0;
	
	//Reset Pin
	gpioUnexport(trig);
	gpioUnexport(Utrig);
	gpioUnexport(echo1);
	gpioUnexport(LED1);
	gpioExport(Utrig);
	gpioExport(echo1);
	gpioExport(LED1);
	gpioExport(trig);
	
	//Set Directions
	gpioSetDirection(trig, 1); // make pin output
	
	//Set Initial State
	gpioSetValue(trig, 0); //turn pin LOW

	cout << "Begin Motor Test" << endl;
	drv.begin();
	
	//set pins using JetsonGPIO Library
	
	drv.selectLibrary(1);
	drv.setMode(DRV2605_MODE_INTTRIG); //send 'go' command
	
	unsigned char effect = 47;
	
	while(1){
		cout << "Effect #" << (int)effect << endl;
		//activate motor trigger
		gpioSetValue(trig, 1);
		drv.setWaveform(0,effect);	//Run Effect #47
		drv.setWaveform(1,0);	//End waveform
		
		drv.go(); //play effect
		usleep(300000); //wait for 3/10 of a sec
		
		//deactivate motor trigger..move on to next motor
		gpioSetValue(trig, 0);
		usleep(300000); //wait for 3/10 of a sec
	}
}

/*  ******  Original Arduino Code bellow *******
 * #include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;


 int motor1 = 5;
 int motor2 = 3;
 //this isa comment

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();

  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
 
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

uint8_t effect = 1;

void loop() {
  Serial.print("Effect #"); Serial.println(effect);

  digitalWrite(motor1, HIGH);

  // set the effect to play
  drv.setWaveform(0, 47);  // play effect 
  drv.setWaveform(1, 0);       // end waveform

  // play the effect!
  drv.go();

  // wait a bit
  delay(300);

  digitalWrite(motor1, LOW);

 
  
  digitalWrite(motor2, HIGH);
  
  // set the effect to play
  drv.setWaveform(0, 47);  // play effect 
  drv.setWaveform(1, 0);       // end waveform

  // play the effect!
  drv.go();

  // wait a bit
  delay(500);

  digitalWrite(motor2, LOW);

  
  
}*/
