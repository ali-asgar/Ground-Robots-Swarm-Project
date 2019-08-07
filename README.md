# Ground-Robots-Swarm-Project
RADLab project 


The Ground-Robots-Swarm-Project repository contains source code for connecting your Arduino Uno with the RoboClaw ST 2x45A Motor Controller and Prowler robot for motion planning. The repository makes use of Roboclaw Library for Arduino.

NOTE: Whenever connecting the Roboclaw, it is necessary to give the serial port adapter files read and write permissions

'sudo chmod 666 /dev/ttyUSB0 /dev/ttyACM0'

## Setting up prerequisites

Clone this repository to your **/Documents/Arduino/libraries** folder

### Hardware Requirements 
- [**Prowler Robot** Kit](https://www.servocity.com/prowler)
- [Prowler Robot Assembly video Tutorial](https://www.youtube.com/watch?v=k7ZXSDlREJM)
- [**Nomad Robot** Kit](https://www.servocity.com/nomad)
- [Nomad Robot Assembly video Tutorial](https://www.youtube.com/watch?v=FAPDkyeAek8)
- [313 RPM HD Premium Planetary Gear Motor w/Encoder](https://www.servocity.com/313-rpm-hd-premium-planetary-gear-motor-w-encoder)
- [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3)
- [RoboClaw ST 2x45A Motor Controller](http://www.basicmicro.com/RoboClaw-ST-2x45A-Motor-Controller_p_27.html)
- [12 AWG Copper Wire](https://www.amazon.com/gp/product/B01AQU3ST8)

### Software Requirements
- [BasicMicro Motion Studio](http://downloads.basicmicro.com/software/BMStudio/setup.exe) for Windows.
- [Arduino IDE](https://www.arduino.cc/en/main/software)

### Connections
Arduino Uno, RoboClaw ST 2x45A and Motor 1 & 2 connections
- Packet Serial Mode - It can transmit and receive serial data, UART

![image](https://user-images.githubusercontent.com/15716059/62593867-67f98b00-b8a6-11e9-9adc-798383b5d7e1.png)

- Motor 2 Gnd  		to  		Arduino Digital Pin Gnd
- Roboclaw Gnd  	to  		Arduino Digital Pin Gnd
- Roboclaw S2  		to  		Arduino Digital Pin 10
- Roboclaw S1  		to  		Arduino Digital Pin 11
- Roboclaw 1A  		to  		Motor 2 Channel A
- Roboclaw 1B  		to  		Motor 2 Channel B
- Roboclaw 5+  		to  		Motor 2 Sensor Voltage +
- Roboclaw 5+  		to  		Motor 1 Sensor Voltage +
- Roboclaw 2A  		to  		Motor 1 Channel A
- Roboclaw 2B  		to  		Motor 1 Channel B
- Roboclaw Gnd  	to  		Motor 1 Gnd

The Motor + and Motor - pins of the 6-pin JST connector are not used. Instead 12 AWG Copper Wires are soldered on the Motors.

## Roboclaw

