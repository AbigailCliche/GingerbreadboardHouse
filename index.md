## This is a Gingerbreadboard House

This faux gingerbread house was constructed by Abigail Cliche and Andrew Hathcock for ECE 4180 (Embedded Systems Design) at The Georgia Intstitute of Technology. 

The goal was to create holiday decor that tickles all of the senses . . . except for taste, ironically. 

| Contents |
| ----------- |
| [Features](#features) |
| [System Block Diagram](#system-diagram) |
| [Components List](#components-list) |
| [Instructions](#instructions) |
| Photos |
| Demo |

# Features

# System Diagram

![Diagram](https://docs.google.com/drawings/d/e/2PACX-1vTWjPZ-bOA0e_O0Pe_Sex509pHJ4QLMW8QS28_QGlQi4vUylisdC-Kt_oVLWizGCfXbXGdRNt-CPInf/pub?w=960&h=720)

# Components List

| Component | Quantity |
| ----------- | ----------- |
| Raspberry Pi v4 | 1 |
| Wall plug 5V power supply | 2 |
| Bluefruit UART Friend | 1 |
| LED Light String | 1 |
| 8GB SD Card | 1 |
| Green or Yellow LED | 2 |
| Analog Speaker | 1 |
| [Dual H-Bridge](https://www.digikey.com/en/products/detail/sparkfun-electronics/ROB-14450/7915576?utm_adgroup=Evaluation%20and%20Demonstration%20Boards%20and%20Kits&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers&utm_term=&utm_content=Evaluation%20and%20Demonstration%20Boards%20and%20Kits&gclid=Cj0KCQiA2af-BRDzARIsAIVQUOdxqqHYdTwMKlwcLaPJsxsejbrNkKA72xdS0uOuaSbkk1pZdwntzpMaAtv9EALw_wcB) | 1 |
| Fancy Feast Can | 1 |
| Jumper Wires M-M | 20 |
| Jumper Wires F-M | 15 |
| [Class D Audio Amplifier](https://www.sparkfun.com/products/11044) | 1 |
| Switch | 1 |
| Wheel | 1 |
| I2C A to D Converter | 1 |
| Photo Resistor | 1 |
| Analog Temperature Sensor | 1 |
| Relay | 1 |
| [Peltier Thermo Module](https://www.adafruit.com/product/1331?gclid=Cj0KCQiA2af-BRDzARIsAIVQUOdZAbHClrYFSsmMw1SOXrySN1djDE4DO7kTtrcx7ZERTygEYAqd_CMaApgZEALw_wcB)| 1 |
| Screw Terminals | 2 |

## Construction Instructions

1. Procure a sturdy yet thin material (we used MDF) for your house, and cut out of it four rectangles of equal size and a pentagonal facade. All edges of the facade except for the base should be equal to the hight of the four rectangles. Drill two small holes at the base of the the first floor windows. You will eventually place tricolor LED "candles" there. Hot glue the pieces into a house shape on top of a base, leaving the "back" of the hosue open.

2. Assemble all components following the block diagram above and insert them into the house enclosure.

3. Load an image of RaspberryPi OS (formery Raspbian) onto the 8GB SD card and insert into the Pi. 

3. Follow the normal pi setup procedure then download the [source code repository](https://github.com/AbigailCliche/GingerbreadboardHouse).

4. Compile the code and run ```main```. You should now be able to use all features of the house and connect it to the [Bluefruit Connect App](https://learn.adafruit.com/bluefruit-le-connect).

## Demo
[Youtube Demo Link](https://youtu.be/ceOeai3Cwcs)
