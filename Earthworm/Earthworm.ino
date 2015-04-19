#include <Servo.h>
#include <AFMotor.h>
#include <PID.h>
#include <EyeStalk.h>
#include <Encoder.h>
#include <Drive.h>


AF_DCMotor frontLeft(2);
AF_DCMotor frontRight(1);
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

void runTest(int b){
  long time = millis();
  rightDrive.setPower(b);
  while(millis() - time < 1000){
    leftEncoder.update();
    rightEncoder.update(); 
  }
  rightDrive.setPower(0);
  Serial.print(b);
  Serial.print("\t");
  Serial.print(leftEncoder.getPosition());
  Serial.print("\t");
  Serial.print(rightEncoder.getPosition());
  Serial.println();
}

void loop() {
  Serial.println("Power\tFront\tBack");
  for(int i = 0; i <= 256; i+= 8){
    runTest(i);
    runTest(-i); 
  }
    
}
