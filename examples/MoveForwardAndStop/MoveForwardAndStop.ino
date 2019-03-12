/*
 * Created in RADLab
 *
 * Project: RoboClaw ST 2x45A Motor Controller with Prowler Robot and Arduino Uno
 *
 * Program Name: MoveForwardAndStop.ino
 * Author: Ali Asgar Tashrifwala
 * Date: 03/12/2019
 *
 * Things to note:
 *
 * (In Arduino IDE)
 *   - Make sure the standard library is connected to the program
 * (In Basicmicro Motion Studio)
 *   - Make sure to go to General Settings, and change the following:
 *        Control Node - Packet Serial
 *        PWM Mode - Locked Antiphase
 *        Serial, Baudrate - 9600 
 *   - Go to file and save it
 * (on RoboClaw board)
 *   - Make sure to go to Change the Mode to 7, i.e., Packet Serial.
 *   - The 3 steps to change the mode on the board is given in the manual
 *         Reference: RoboClaw Series User Manual Page 35
 *         Mode - 7, Function - Packet Serial Mode - Address 0x80, 
 *         Description - 
 *         Control using packet serial mode with a specific address for 
 *         networking several motor controllers together.
 *               
 * Purpose of this file: to move the robot forward and stop
 * Program 1
 * 
 */

#include <SoftwareSerial.h>  //Step 1: Setup Serial library for communication
#include "RoboClaw.h"        //Step 2: Includes required to use Roboclaw library
#define address 0x80         // Roboclaw is set to Packet Serial Mode (See Above)

// The SoftwareSerial library has been developed to allow serial communication 
// on other digital pins of the Arduino, using software to replicate the 
// functionality called UART on pins 0 and 1 of Arduino Hardware.

SoftwareSerial terminal(10,11);        
// RX is digital pin 10 (connect to TX of other device)
// TX is digital pin 11 (connect to RX of other device)
RoboClaw roboclaw(&terminal, 10000);   
// RoboClaw.h - (SoftwareSerial *sserial,uint32_t tout)

//Step 3a: Initialize Velocity PID coefficients for Motor 1
#define Kp1 1.0
#define Ki1 0.0
#define Kd1 0.5
#define qpps 44000
//Step 3b: Initialize Velocity PID coefficients for Motor 2
#define Kp2 5000.0
#define Ki2 1.0
#define Kd2 1.0

void setup() {
    //Step 4: Open Serial and roboclaw serial ports
    Serial.begin(9600);       
    roboclaw.begin(9600);
    //Adjust the same on board using Basicmicro motion studio (See Above)
    
    //Step 5: Set PID Coefficients
    roboclaw.SetM1VelocityPID(address,Kd1,Kp1,Ki1,qpps);
    roboclaw.SetM2VelocityPID(address,Kd2,Kp2,Ki2,qpps);
}

void loop() {
    char i; 
    if (Serial.available() > 0) {
        i = Serial.read();       // reading data from serial monitor
    }  
    if(i == 'w' || i == 'W' ) { // The robot moves forward
    roboclaw.ForwardM1(address,25);
    roboclaw.ForwardM2(address,24);
    delay(10);
    }
    if(i == ' ') {              // The robot stops
    roboclaw.ForwardM1(address,0);
    roboclaw.ForwardM2(address,0);
    delay(10);
    }
    displayspeed();
}

void displayspeed(void) {
    uint8_t status1,status2,status3,status4;
    bool valid1,valid2,valid3,valid4;
    float alpha = 0.1;  
    // 0.1 = data smoothing single pole filter setting. in displayspeed()
 
    int32_t enc1 = roboclaw.ReadEncM1(address, &status1, &valid1);
    int32_t enc2 = roboclaw.ReadEncM2(address, &status2, &valid2);
    int32_t speed1 = roboclaw.ReadSpeedM1(address, &status3, &valid3);
    int32_t speed2 = roboclaw.ReadSpeedM2(address, &status4, &valid4);

    // alpha is used to filter the results in displayspeed()
    long avgSpeedM1 = avgSpeedM1 * (1-alpha) + speed1 * alpha;
    long avgSpeedM2 = avgSpeedM2 * (1-alpha) + speed2 * alpha;
    
    Serial.print("Encoder1:");
    if(valid1){
        Serial.print(enc1,DEC);
    }
    Serial.print("  Encoder2:");
    if(valid2){
        Serial.print(enc2,DEC);
    }
    Serial.print("  Avg Speed1:");
    if(valid3){
        Serial.print(avgSpeedM1,DEC);
    }
    Serial.print("  Avg Speed2:");
    if(valid4){
        Serial.print(avgSpeedM2,DEC);
    }
    Serial.println();
}

