/**
 *
 * Project: Wheel and Paddle
 * Author: Kim Lilliestierna
 * Creation Date: 2020-Sep-15
 * Copyright: (c) 2021 Kim Lilliestierna (kill@itr.no)
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 
 *
 * Digistamp Pro firmware for Dexxa Stering wheel conversion
 * using a DigistumpPro clone.
 *
 * Based on the Digistamp DigiJoystick example in the Arduino board package 
 * which in turn is based on the V-Usb implementation 
 *
 * the Dexa itself was modifed:
 * Spit out the accelerator and break pedals into separate channels.
 * added +5V and ground to the cable.
 * reconnected the potentiometers in voltage spliter configuration.
 * Same was done to the stering wheel.
 * 
 * For Kicad shematics se the Docs directory 
 */
#include <Arduino.h>

#define DEBUG

#include "Wheel.h"

// pin maping is all over the place  due to USB pins/ serial pins/ and ucked up Analog-SPIclock interference
//
#define DownShiftPin			 0
#define UpShiftPin 				 2
#define LeftWheelPin			 9
#define RightWheelPin			 8

#define WheelPin				10
#define WheelPin_Analog			A10

// cant use pin 11 since there is a serial clock contaminating the analog read
// When i figure out hwo to disable the spi clock ....

#define AccellPedalPin			 5
#define AccellPedalPin_Analog	A5
#define BreakPedalPin			12
#define BreakPedalPin_Analog	A12

// buttons debounce delay 50 ms
#define DEBOUNCE_DELAY 50

// Blue onboard led
#define BLUE 1

uint8_t buttonState;			// packed bit array of buttons to send of to USB
bool buttonChanged;				// change flag

uint16_t accellOff;				// Accelerator pedal offset, compensating for non zero pot position
uint16_t breakOff;				// Break pedal offset for the same reason


// Button struct
typedef struct btn {
	uint8_t pin;				// pin to button
	bool state;					// last state
	unsigned long lastTime;		// Last time checked
} Button;


volatile Button buttons[4];


#ifdef DEBUG
/** Blink the blue led
 */
void blink() {
  static bool bLed = true;
		if (bLed) {
	    	digitalWrite(BLUE,LOW);
	    	bLed=false;
		} else {
	    	digitalWrite(BLUE,HIGH);
	    	bLed=true;
		}
}
#endif

/** Get buttons states
 *
 * return: true if button changed since last call false otherwise
 */
bool checkButtons() {
	bool state;
	bool changed = false;
	unsigned long now=millis();

	// go through all the buttons and check which one changed if anny
	for(int i=0;i<4;i++) {
		Wheel.update(); //keep usb fed
		state=digitalRead(buttons[i].pin)==HIGH?true:false;
		// debounce
		if ((state != buttons[i].state)  && now-buttons[i].lastTime>DEBOUNCE_DELAY) {
			buttons[i].state = state;
			// Buttons changed update global bitmap
			buttonState = state? buttonState & ~(1<<i) : buttonState | 1<<i;  // inverse logic, button active low
			changed=true;
		}
	}
	return changed;
}

/** setup()
 *
 * Setup the hardware etc
 */
void setup() {

	uint16_t temp;
#ifdef DEBUG
	// serial tx / rx on pin 6 / 7
	Serial.begin(9600);
	Serial.println(" Starting up");
#endif
  
	// Init button pins
	buttons[0].pin = UpShiftPin;
	buttons[1].pin = DownShiftPin;
	buttons[2].pin = RightWheelPin;
	buttons[3].pin = LeftWheelPin;


	pinMode(AccellPedalPin,INPUT);
	pinMode(BreakPedalPin,INPUT);
	pinMode(WheelPin,INPUT);
	
	analogReference(0);	//Make sure to reference to Vcc

	// figure out offsets for accell and break pedals since pots do not go all the way to zero
	accellOff=breakOff=0;
#ifdef DEBUG
	Serial.println(" Setting Offsets");
#endif
	for (int i=0;i<50;i++) {	// loop along for a while and find the highest point
		//
		// Accellerator
		temp=analogRead(AccellPedalPin_Analog);
		if (temp > accellOff) accellOff=temp;
		delay(10); // wait around just a bit for stuff to perhaps settle

		// Break
		temp=analogRead(BreakPedalPin_Analog);
		if (temp > breakOff) breakOff=temp;
		delay(10);
	}
	Serial.println(" Initializing buttons");
	
	// initialize button struct and buttons pins
	for (int i=0;i<4;i++) {
		buttons[i].lastTime=0;
		buttons[i].state=false;
		pinMode(buttons[i].pin,INPUT_PULLUP);
	}

	// blue led
	pinMode(BLUE,OUTPUT);

#ifdef DEBUG
	// startup  blink..
	for (int i=0;i<5;i++){
		blink();
		Wheel.delay(200);
		blink();
		Wheel.delay(200);
	}
#endif

	buttonState=0;
	buttonChanged=false;

#ifdef DEBUG
	Serial.println(" Setup Done");
#endif
}

/** actually do something ....
 *
 */
void loop() {

  	uint16_t atemp;	// temporary analog values
	uint16_t btemp;

	uint16_t wheelVal;			// wheel position
	static uint16_t oldWheel=0;

	uint16_t accellVal;			// Accelerator
	static uint16_t oldAcell=0;

	uint16_t breakVal;			// Break
	static uint16_t oldBreak=0;

	Wheel.delay(25); // wait 50 milliseconds and push out usb if needed

	wheelVal=analogRead(WheelPin_Analog);	// get wheel position
	
	// get pedal values and compensate for offset
	// since the lines are noicy this might still result in a negative value , usualy -1 or -2
	// if so set it to zero
	
	atemp=analogRead(AccellPedalPin_Analog);
	accellVal=(atemp>accellOff)?atemp-accellOff:0;  // dont bother if not above offest value

	btemp=analogRead(BreakPedalPin_Analog);
	breakVal=(btemp>breakOff)?btemp-breakOff:0;     // same

 	buttonChanged=checkButtons();					// check i any buttons have been pressed

	// Anything changed yet ?
	if (buttonChanged || (wheelVal != oldWheel) || (accellVal != oldAcell) || (breakVal != oldBreak)) {

#ifdef DEBUG		
		Serial.print("Buttons:");
		for (int i=0;i<4;i++) {
			Serial.print(buttons[i].state?1:0);
		}
		Serial.print(" ");
		Serial.print(buttonState);
		Serial.print(" W:");
		Serial.print(wheelVal);
		Serial.print(" A:");
		Serial.print(accellVal);
		Serial.print(" B:");
		Serial.println(breakVal);
#endif

		// Push values into the USB report
		Wheel.setX(wheelVal);
		Wheel.setY(accellVal);
		Wheel.setXROT(breakVal);


		Wheel.setButtons(buttonState);
		
		// remember for next time
		oldWheel=wheelVal;
		oldAcell=accellVal;
		oldBreak=breakVal;

		buttonChanged = false;

#ifdef DEBUG
		blink();
#endif
	}
}
