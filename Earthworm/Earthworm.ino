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

byte linearizeFrontRight(byte a){
  byte c = (byte)
    44.45465483435341560849
    +0.98609626925931246578*a
    -0.00484368205548453933*pow(a,2)
    +0.00001629688671282127*pow(a,3);
  return c;
}

byte linearizeRearRight(byte a){
  byte c = (byte)
    27.84288958245133302535
    +0.90111481827045730186*a
    -0.00698164966681606366*pow(a,2)
    +0.00002473216788024596*pow(a,3);
  return c;
}

byte linearizeRearLeft(byte a){
  byte c = (byte)
    23.93100035122453460246 
    +1.44356023196589119536*a
    -0.00330914040337424765*pow(a,2)
    +0.00000549281824008921*pow(a,3);
  return c; 
}

byte linearizeFrontLeft(byte a){
  byte c = (byte)
    23.93100035122453460246 
    +1.44356023196589119536*a
    -0.00330914040337424765*pow(a,2)
    +0.00000549281824008921*pow(a,3);
  return c; 
}

Encoder leftEncoder(16,17);
Encoder rightEncoder(18,19);

PID leftPID(0.0,0.0,0.0);
PID rightPID(0.0,0.0,0.0);
PID turnPID(0.0,0.0,0.0);

Drive leftDrive(&frontLeft, &rearLeft, &leftEncoder, &leftPID, linearizeRearLeft, linearizeFrontLeft);
Drive rightDrive(&frontRight, &rearRight, &rightEncoder, &rightPID, linearizeRearRight, linearizeFrontRight);

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
  rightEncoder.reset();
  leftEncoder.reset();
  long time = millis();
  Serial.print(b);
  Serial.print("\t");
  leftDrive.setLinearPower(b);
  while(millis() - time < 1000){
    leftEncoder.update();
    rightEncoder.update(); 
  }
  leftDrive.setPower(0);
  delay(1000);
  Serial.print(leftEncoder.getPosition());
  Serial.print("\t");
  Serial.print(rightEncoder.getPosition());
  Serial.println();
}

void loop() {
  Serial.println("Power\tFront\tBack");
  for(int i = -256; i <= 256; i+= 8){
    runTest(i);
  }
    
}
