# GingerbreadHouse
## Features
* Raspberry Pi v4
  * Using [WiringPi](http://wiringpi.com/)
* LED Christmas Lights
  * Modified Storebought LEDs attached with screw terminals
  * Night mode with LED effects
* Bluefruit BLE Control
  * Tried to use [GattLib](https://github.com/labapart/gattlib) but it was too buggy
  * Used Bluefruit UART Friend with [WiringpiSerial](http://wiringpi.com/reference/serial-library/)
    * [Here](https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c) is good reference material on using the RPi 4's UART
* Relay-controlled Heating Element
* External Power Supply
* Christmas Music
  * Volume controlled by potentiometer
