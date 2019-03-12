/*
 * Created in RADLab
 *
 * Project: RoboClaw ST 2x45A Motor Controller with Prowler Robot and Arduino Uno
 *
 * Program Name: testrobot.ino
 * Author: Ali Asgar Tashrifwala
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
 * Purpose of this file: to move the robot in a straight line
 * Software Architecture:
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
    
    uint8_t status1,status2,status3,status4;
    bool valid1,valid2,valid3,valid4;

    int32_t enc1= roboclaw.ReadEncM1(address, &status1, &valid1);
    int32_t enc2= roboclaw.ReadEncM2(address, &status2, &valid2);

    //the coordinates of x and y are in metres and angle is in degrees.
    float radius, theta, arc, x_coordinate = 1, y_coordinate = 1, ratio = 1, w = 0.86; 
    int s1 = 24, s2;

    // Finding the radius (or Distance), Angle and Circumference of the Arc
    radius = robot_move_r(x_coordinate, y_coordinate);
    //Serial.println(radius,DEC);
    theta = robot_move_theta(x_coordinate, y_coordinate);
    //Serial.println(theta,DEC);
    arc = robot_move_arc(radius, theta);
    //Serial.println(arc,DEC);

    // Finding the speeds of the of Motor M1 and Motor M2 using ratios
    ratio = (2*radius - w)/(2*radius + w);
    //Serial.println(ratio,DEC);
    s2 = round(s1 / ratio);
    //Serial.println(s2,DEC);

    // Calculating Radius Angle and Arc Circumference in encoder value
   
    // One complete roation of the tire of circumference 17 inch ≈ 1290 encoder events.
    // Therefore, 1 inch ≈ 76 encoder events.             (= 75.8)
    // 1 meter = 2985 encoder events (1 meter = 39.37 inch x 75.8 = 2985)
    // 1 foot  =  910 encoder events (1 foot  =    12 inch x 75.8 =  910)
    
    radius = (radius * 910); // encoder values are calculated from the radius.
    //Serial.println(radius,DEC);
    theta = theta*13.0;      // theta for the zero point rotation of the rover.
    //Serial.println(theta,DEC);
    arc = theta*39.55*8;
    //Serial.println(arc,DEC);
   
    // Hard coding values of variables for purpose of testing
    radius = 8000;
    s2 = 25;
    
    if(enc1 <= radius)  {
       roboclaw.ForwardM1(address,s1);    
       roboclaw.ForwardM2(address,s2);
    }
    if(enc1 > radius)  {
      roboclaw.ForwardM1(address,0);
      roboclaw.ForwardM2(address,0);
    }
    displayspeed();
}

// The Following code below is prepared for use in any code (Just copy and paste)

float robot_move_r(float a, float b) {
  return sqrt((a*a)+(b*b)); // radius is sqrt(a^2 + b^2)
}

float robot_move_theta(float a, float b) {
  return round(atan(b/a) * 57.296);  
  //theta is tan inverse (b/a) and converted from radians to degrees
}

float robot_move_arc(float radius, float theta) {
  return 2 * 3.14 * radius * (theta/360);  
  // arc is circumference 2*pi*r*theta/360 
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
        // Serial.print("  Status1:");
        // Serial.print(status1,HEX);
    }
    else {
        Serial.print("failed ");
    }
    
    Serial.print("  Encoder2:");
    if(valid2){
        Serial.print(enc2,DEC);
        // Serial.print("  Status1:");
        // Serial.print(status1,HEX);
    }
    else {
        Serial.print("failed ");
    }
    
    Serial.print("  Avg Speed1:");
    if(valid3){
        Serial.print(avgSpeedM1,DEC);
        // Serial.print("   Speed1:");
        // Serial.print(speed1,HEX);
    }
    else {
        Serial.print("failed ");
    }
 
    Serial.print("  Avg Speed2:");
    if(valid4){
        Serial.print(avgSpeedM2,DEC);
        // Serial.print("   Speed2:");
        // Serial.print(speed2,HEX);
    }
    else {
        Serial.print("failed ");
    }
    Serial.println();
}

