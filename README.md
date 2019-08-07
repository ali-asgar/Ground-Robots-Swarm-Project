# Ground-Robots-Swarm-Project
The Ground-Robots-Swarm-Project repository contains source code for connecting your Arduino Uno with the RoboClaw ST 2x45A Motor Controller and Prowler robot for motion planning. The repository makes use of Roboclaw Library for Arduino.

NOTE: Whenever connecting the Roboclaw, it is necessary to give the serial port adapter files read and write permissions.

`sudo chmod 666 /dev/ttyUSB0 /dev/ttyACM0`

## Setting up prerequisites
Clone this repository to your **/Documents/Arduino/libraries** folder.

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
- [BasicMicro Motion Studio](http://downloads.basicmicro.com/software/BMStudio/setup.exe) The setup is in .exe format so it will only work on Windows OS.
- [Arduino IDE](https://www.arduino.cc/en/main/software)

### Connections - Arduino Uno, RoboClaw ST 2x45A and Motor 1 & 2 connections
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

The Motor + and Motor - pins of the 6-pin JST connector are not used because the wires are not thick enough. 
Instead 12 AWG Copper Wires are soldered on the Motors.

![image](https://user-images.githubusercontent.com/15716059/62594138-69778300-b8a7-11e9-8752-95d427e8405d.png)
![image](https://user-images.githubusercontent.com/15716059/62594156-74caae80-b8a7-11e9-970b-f818676db11b.png)

## Roboclaw Motor Controller
A [Motor Controller](https://www.robotshop.com/community/tutorials/show/basics-what-is-a-motor-controller) is a device that acts as intermediary between your robot’s microcontroller, batteries and motors. A motor controller is necessary because a microcontroller can usually only provide roughly 0.1 Amps of current whereas most actuators (DC motors, DC gear motors, servo motors etc.) require several Amps.

A [motor controller](https://en.wikipedia.org/wiki/Motor_controller) might include a manual or automatic means for starting and stopping the motor, selecting forward or reverse rotation, selecting and regulating the speed, regulating or limiting the torque, and protecting against overloads and faults.

RoboClaw is the name of the motor controller series made by [BasicMicro](http://www.basicmicro.com/). The Model which we are using is **RoboClaw ST 2x45A Motor Controller**. [Documentation and Resources.](https://www.basicmicro.com/downloads)

![image](https://user-images.githubusercontent.com/15716059/62594818-f28fb980-b8a9-11e9-9197-c5db8776cc92.png)

### Setup
Connect the RoboClaw ST 2x45A with the computer (Windows) with USB to micro USB cable. From the power supply give 12V DC at the positive and negative terminal of the RoboClaw ST 2x45A. You will see the board in the attached devices section.

![image](https://user-images.githubusercontent.com/15716059/62594839-0cc99780-b8aa-11e9-8fb5-e19b41539b4b.png)

![image](https://user-images.githubusercontent.com/15716059/62594861-1eab3a80-b8aa-11e9-906b-fc244374243b.png) Click on Connect Selected Unit.

![image](https://user-images.githubusercontent.com/15716059/62594955-7f3a7780-b8aa-11e9-9066-814680bef03e.png) 

The RoboClaw ST 2x45A gets connected to the BasicMicro Motion Studio.

We can see that all the parameter are GREEN in color which means everything is good. We can also see the current temperature, encoder, speed, battery level and version in the top section.
We can also see different settings such as General, PWM, velocity and Position settings on the left side.

In the Studio, go to General Settings, and change the following:
```
Control Mode: Packet Serial
PWM Mode: Locked Antiphase
Serial, Baudrate: 9600
```
Go to file and save it.

### Change the mode to Packet Serial on Roboclaw:
- Function: Packet Serial     Mode - Address 0x80				Mode: 7
- Description: It can transmit and receive serial data, UART

The 3 buttons on RoboClaw are used to set the different configuration options. The MODE button sets the interface method such as Serial or RC modes. The SET button is used to configure the options for the mode. The LIPO button doubles as a save button and configuring the low battery voltage cut out function of RoboClaw. To set the desired mode follow the steps below. 

![image](https://user-images.githubusercontent.com/15716059/62595001-95e0ce80-b8aa-11e9-94c4-09566fadb32c.png)

1. Press and release the MODE button to enter mode setup. The STAT2 LED will begin to blink out the current mode. Each blink is a half second with a long pause at the end of the count. Five blinks with a long pause equals mode 5 and so on. 
2. Press SET to increment to the next mode. Press MODE to decrement to the previous mode. 
3. Press and release the LIPO button to save this mode to memory.

### Instructions for Arduino Uno
-	Clone this repository to your **/Documents/Arduino/libraries** folder. 
- Also, you can download this repository, unzip the file and copy it in /Documents/Arduino/libraries folder.
-	Start Arduino IDE (Restart Arduino IDE if already open.)
-	Connect Arduino Uno with computer (or Raspberry Pi if you are using it.)
-	Go to File -> Examples -> Examples from custom libraries -> Ground-Robots-Swarm-Project ->testrobot.

![image](https://user-images.githubusercontent.com/15716059/62595420-48fdf780-b8ac-11e9-95a3-4a82019519fd.png)

![image](https://user-images.githubusercontent.com/15716059/62595449-6fbc2e00-b8ac-11e9-8a52-4c8c75ed0af4.png)
 Go to Tools -> Board -> “Arduino/Genuino Uno”.

![image](https://user-images.githubusercontent.com/15716059/62595455-79de2c80-b8ac-11e9-9fd5-c7fb448c42e0.png) Go to Port -> Select port with Arduino/Genuino Uno.

Make changes if necessary, verify and upload the sketch.

![image](https://user-images.githubusercontent.com/15716059/62595505-94180a80-b8ac-11e9-9751-4e20e3ff3a70.png) Open serial monitor and set baud rate to 9600.

## The Example codes

**Required Information - Encoder values**

When the tire completes 1 rotation, we see this value on the software.
- Countable Events Per Revolution (Output Shaft) - 1,288.848

When the tire completes 1 rotation, the encoder rotates these many times.
- Encoder: Cycles Per Revolution (Output Shaft) - 322.212

Therefore, 1 cycle of Encoder = 4 Events on software
- 322.212 cycles of Encoder = (322.212 x 4) = 1288.848 ≈ 1288 Events on software

The circumference of tire = Pi x Tire Diameter = 3.14 x 5.4 inch = 16.956 inches ≈ 17 inches.
- Therefore, 17 inches = 1288 events
