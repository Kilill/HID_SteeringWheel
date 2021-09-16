/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 * Modified for Digispark by Digistump
 * And now modified by Sean Murphy (duckythescientist) from a keyboard device to a joystick device
 * And now modified by Bluebie to have better code style, not ruin system timers, and have delay() function
 * Most of the credit for the joystick code should go to Rapha�l Ass�nat
 * Modified Sep/2021 by Kim Lilliestierna for Dexxa Steering Wheel conversio.
 */

#ifndef __Wheel_h__
#define __Wheel_h__
 
#define GCN64_REPORT_SIZE 8

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "usbdrv.h"
#include "oddebug.h"
#include "usbconfig.h"
 
// Data buffer for transmission
uint8_t builtReport[GCN64_REPORT_SIZE];
uint8_t reportBuffer[GCN64_REPORT_SIZE];

// report frequency set to default of 50hz
#define DEFAULT_REPORT_INTERVAL 20
static unsigned char idle_rate = DEFAULT_REPORT_INTERVAL / 4; // usb magic ... in units of 4ms
static unsigned long last_report_time = 0;

// Deexa stering wheel and pedals originally only had 2 axis, the steering weel itself and the
// the accelerator and break pedals counter connectet. modifed to now have separate axis
// The original Joystick setup only 8bit for each axis but the adc as a 10bit range
// descriptor also modifed to have 16bit axis

// Hid Reort Descriptot
// !!!! if you change the length of this you must update USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH  in usbconfig.h
const unsigned char gcn64_usbHidReportDescriptor[] PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X) (steering wheel)
    0x09, 0x31,                    //     USAGE (Y) (accellerator)
    0x09, 0x33,                    //     USAGE (Rx) (break)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x03,              //     LOGICAL_MAXIMUM (32767)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //     END_COLLECTION
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)  
    0x29, 0x04,                    //   USAGE_MAXIMUM (Button 4) 2 buttons on wheel and two on the shifter stick
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x10,                    //   REPORT_COUNT (16)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           //     END_COLLECTION
};
// USB device descriptor
#define USBDESCR_DEVICE					1
const unsigned char usbDescrDevice[] PROGMEM = {
		18,							// sizeof(usbDescrDevice): length of descriptor in bytes
		USBDESCR_DEVICE,			// descriptor type
		0x01, 0x01,					// USB version supported
		USB_CFG_DEVICE_CLASS,
		USB_CFG_DEVICE_SUBCLASS,
		0,							// protocol
		8,							// max packet size
		USB_CFG_VENDOR_ID,			// 2 bytes
		USB_CFG_DEVICE_ID,			// 2 bytes
		USB_CFG_DEVICE_VERSION,		// 2 bytes
		1,							// manufacturer string index
		2,							// product string index
		0,							// serial number string index
		1,							// number of configurations
};

class SteeringWheel {
	private:
	static bool mustReport;
	
 public:
	SteeringWheel () {
		cli();
		usbDeviceDisconnect();
		_delay_ms(250);
		usbDeviceConnect();
		usbInit();
		
		sei();
		
		last_report_time = millis();
	}
	
	void update() {
		usbPoll();				// handle USB activity
		
		// instead of above code, use millis arduino system to enforce minimum reporting frequency
		unsigned long time_since_last_report = millis() - last_report_time;
		if (time_since_last_report >= (idle_rate * 4 /* in units of 4ms - usb spec stuff */)) {
			last_report_time += idle_rate * 4;
			mustReport = 1;
		}
	
		// if we want to send a report, signal the host computer to ask us for it with a usb 'interrupt'
		if (mustReport) {
			if (usbInterruptIsReady()) { 	// Is USB ready for another packet ?
				mustReport = 0;
				memcpy(reportBuffer, builtReport, GCN64_REPORT_SIZE);
				usbSetInterrupt(reportBuffer, GCN64_REPORT_SIZE);
			}
		}
	}
	
	// delay while updating until we are finished delaying
	void delay(long milli) {
		unsigned long last = millis();
	  while (milli > 0) {
	    unsigned long now = millis();
	    milli -= now - last;
	    last = now;
	    update();
	  }
	}
	
	void setX(uint16_t value) {
		builtReport[0] = (uint8_t) value&0xff;
		builtReport[1] = (uint8_t) (value>>8)&0xff;
		mustReport=true;
	}
	
	void setY(uint16_t value) {
		builtReport[2] = (uint8_t)value&0xff;
		builtReport[3] = (uint8_t) (value>>8)&0xff;
		mustReport=true;
	}
	
	void setXROT(uint16_t value) {
		builtReport[4] = (uint8_t)value&0xff;
		builtReport[5] = (uint8_t) (value>>8)&0xff;
		mustReport=true;
	}
	
	void setButtons(unsigned char buttons) {
		builtReport[6] = buttons;
		mustReport=true;
	}
	
	void setButtons(char low,char high) {
		setButtons(*reinterpret_cast<unsigned char *>(&low),*reinterpret_cast<unsigned char *>(&high));
	}
};

// Create global singleton object for users to make use of and initalize the static
bool SteeringWheel::mustReport=false;
SteeringWheel Wheel = SteeringWheel();


// Public functions that will get called by the USB subsystem

#ifdef __cplusplus
extern "C"{
#endif 
	// USB_PUBLIC uint8_t usbFunctionSetup
	
	uint8_t usbFunctionSetup(uint8_t data[8]) {
		usbRequest_t *rq = (usbRequest_t *)data;

		usbMsgPtr = reportBuffer;
		if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {	// class request type
			if (rq->bRequest == USBRQ_HID_GET_REPORT){ 						// wValue: ReportType (highbyte), ReportID (lowbyte)
				// we only have one report type, so don't look at wValue
				return GCN64_REPORT_SIZE;
			} else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
				usbMsgPtr = &idle_rate;
				return 1;
			} else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
				idle_rate = rq->wValue.bytes[1];
			}
		} else {
			/* no vendor specific requests implemented */
		}
		return 0;
	}

	uint8_t usbFunctionDescriptor(struct usbRequest *rq) {
		if ((rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_STANDARD) {
			return 0;
		}

		if (rq->bRequest == USBRQ_GET_DESCRIPTOR) {
			// USB spec 9.4.3, high byte is descriptor type
			switch (rq->wValue.bytes[1]) {
				case USBDESCR_DEVICE:
					usbMsgPtr = usbDescrDevice;
					return sizeof(usbDescrDevice);
					break;
					
				case USBDESCR_HID_REPORT:
					usbMsgPtr = gcn64_usbHidReportDescriptor;
					return sizeof(gcn64_usbHidReportDescriptor);
					break;
			}
		}
		return 0;
	}
	
#ifdef __cplusplus
} // extern "C"
#endif


#endif // __Wheel__
