#include <Servo.h>
#include <AFMotor.h>
#include <PID.h>
#include <EyeStalk.h>
#include <Encoder.h>
#include <Drive.h>


AF_DCMotor frontLeft(1);
AF_DCMotor frontRight(2);
AF_DCMotor rearLeft(3);
AF_DCMotor rearRight(4);

Encoder leftEncoder(16,17);
Encoder rightEncoder(18,19);

PID leftPID(0.0,0.0,0.0);
PID rightPID(0.0,0.0,0.0);
PID turnPID(0.0,0.0,0.0);

Drive leftDrive(&frontLeft, &rearLeft, &leftEncoder, &leftPID);
Drive rightDrive(&frontRight, &rearRight, &rightEncoder, &rightPID);

Servo leftServo;
Servo rightServo;

EyeStalk leftEye(14, &leftServo);
EyeStalk rightEye(15, &rightServo);

void setup() {
  Serial.begin(9600);
  leftServo.attach(10);
  rightServo.attach(9);
}

void loop() {
  for(int i = 10; i < 180; i += 10){
    leftEye.servoWrite(i);
    rightEye.servoWrite(i);    
    Serial.print(i);
    Serial.print("\tLeft\t");
    Serial.print(leftEye.getDistance());
    Serial.print("\tRight\t");
    Serial.print(rightEye.getDistance());
    Serial.println();
    delay(1000);
  }
}
