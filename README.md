# HID_SteeringWheel
Dexxa Stering wheel conversion to USB


Granson dug up an old Logitech Dexxa steering wheel with foot pedals from the
attic and asked if i could fix it so that it could connect to the PC.

Since it was orginally designed with a gameport connector, i decided to see if
i couldn't convert it to USB HIF Joystick device, and it so happend i had a 
couple of Digispark Pro clones laying around , and the digispark package for
the Arduino IDE has a USB Joystick example.

That seemed like a good base to start from.

## Hardware

Schematics are located in the Docs folder


### Foot Pedal Pedal Assembly

Having a look at the footpedals it turns out that the pots are connected
together in an backwards serial way. Pressing the accelerator would decrease
the resitance pressing the break would increase it. Very clever to get away with only
2 wires. But i thought it would be neat to have the break separate.
The pedals are connected to the stering wheel case via 2 RJ9 connectors and a cable
and the RJ9 as 4 connections so i rebuilt the pedal connections to use separate pots
and added +5v and Ground to the soup.

![Pedal Connections](/Docs/PedalConnections.png)

### Steering Wheel Assembly

Did the same with the steering wheel pot.
For some reason the original designers decided to use different colored wires,
which is good, but decided that the Black wire should be used as a signal cable,
when most of the rest of the world think that is should ground, so beware.

### Control board

I decided to remove the old connector board for the Gameport card and make a new
one on a prototype board.

5 pins on the Dispark Pro is used for USB,Serial and Onboard LED 
ie Pin 0,3,4,6,7 and using PIN 11 for analog in was not possible since it 
doubles as the SPI clck and for was bleeding over the clock to the analog 
readings. I spread the connections out on the rest of the pins.

![Wheel Assembly](/Docs/WheelConnections.png)

## Software

Its based it on the DigiJoystick example from the Arduino Digispark package.
Since i had to modify it i added it as a library in the lib directory.

The original DigiJoystick example was configured with 6 8Bit analog axis and 
14 buttons 8Bit is a bit low and i only needed 3 Axis and 4 buttons. So 
converted the original DigiJoystic.h into a Wheel.h and modified the orginal
USB Hid Report descriptor to have 3 16Bit axis and 4 buttons this still 
fits within the 8 byte constraint of a simple usb hid report.




## Development enviroment

I'm not overly fond of the Arduino IDE so have been using VScode and the PlatformIO extension instead, 
but it should be triviall to convert the main.cpp to an .ino file

the Digispark Pro comes with the micronuclus bootlader alredy installed, and
you will need this to upload to the board. And Arduino IDE/Platformio *should* pull that in
If using the Arduino ide you will need to add Digistump AVR Boards in the board manager.

You can get that here [https://github.com/micronucleus/micronucleus](https://github.com/micronucleus/micronucleus)

If you decide to use Platformio you will need to change the path to the 
micronucluos uploader in the platform.io file

### License

The orginal Digispark code is released under a GPLv2 / 3 license
So this code is as well.

And the usual caveats aply:
Software is "as is" and might do unexpected things, use at your own discretion.
