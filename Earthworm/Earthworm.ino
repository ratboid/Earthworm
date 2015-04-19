#include <Servo.h>
#include <AFMotor.h>
#include <PID.h>
#include <EyeStalk.h>
#include <Encoder.h>
#include <Drive.h>

#define WIDTH 9.5

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

Encoder leftEncoder(18,19);
Encoder rightEncoder(16,17);

PID leftPID(11.5,0.0,0.0);
PID rightPID(11.5,0.0,0.0);
PID turnPID(192.0,0.0,0.0);

Drive leftDrive(&frontLeft, &rearLeft, &leftEncoder, &leftPID, linearizeRearLeft, linearizeFrontLeft);
Drive rightDrive(&frontRight, &rearRight, &rightEncoder, &rightPID, linearizeRearRight, linearizeFrontRight);

Servo leftServo;
Servo rightServo;

EyeStalk leftEye(14, &leftServo);
EyeStalk rightEye(15, &rightServo);

class Rosed{
  public:
    Rosed(Drive *, Drive *, EyeStalk *, EyeStalk *, PID *);
    void driveDistance(float);
    void turnAngle(float);
    void updateState();
  private:
    Drive * leftDrive;
    Drive * rightDrive;
    EyeStalk * leftEye;
    EyeStalk * rightEye;
    PID * turnController;
    float x,y,theta;
};

Rosed::Rosed(Drive * ld, Drive * rd, EyeStalk * le, EyeStalk * re, PID * tc){
  this->leftDrive = ld;
  this->rightDrive = rd;
  this->leftEye = le;
  this->rightEye = re;
  this->turnController = tc;
}

void Rosed::updateState(){
  float left_del = leftDrive->encoder->getDelta();
  float right_del = rightDrive->encoder->getDelta();
  
  float theta_del = (left_del - right_del) / WIDTH;
  this->theta += theta_del;
  
  this->x += (left_del + right_del) * cos(theta);
  this->y += (left_del + right_del) * sin(theta);

  Serial.print(this->theta);
  Serial.print("\t");
  Serial.print(this->x);
  Serial.print("\t");
  Serial.print(this->y);
  Serial.println("\t");
}

void Rosed::turnAngle(float target_theta){
  long time;
  int signal;
  turnController->reset();
  while(abs((this->theta - target_theta)) > PI/8){
    signal = turnController->step(this->theta,target_theta);
    Serial.print(signal);
    Serial.print("\t");
    leftDrive->setLinearPower(-signal);
    rightDrive->setLinearPower(signal);
    time = millis();
    while(millis()-time < 50){
      rightDrive->encoder->update();
      leftDrive->encoder->update();
    }
    this->updateState();
  }
  leftDrive->setPower(0);
  rightDrive->setPower(0);
}

void Rosed::driveDistance(float dist){
  leftDrive->setGoal(dist);
  rightDrive->setGoal(dist);
  long time;
  while(abs(leftDrive->getError()) > 1 || abs(rightDrive->getError())>1){
    rightDrive->step();
    leftDrive->step();
    time = millis();
    while(millis()-time < 50){
      rightDrive->encoder->update();
      leftDrive->encoder->update();
    }
    this->updateState();
  }
  leftDrive->setPower(0);
  rightDrive->setPower(0);
}

Rosed earthworm(&leftDrive,&rightDrive,&leftEye,&rightEye,&turnPID);
int dest; //distace to motor in inches
float traveled; //distance already covered in y (directly forward) direction

void setup() {
  Serial.begin(9600);
  leftServo.attach(9);
  rightServo.attach(10);
}

void loop() {
  
  /*
  earthworm.turnAngle(-PI);
  earthworm.driveDistance(30);
  earthworm.turnAngle(45);
  earthworm.driveDistance(30);
  */
  //main drive code here
  while (traveled <= dest){
    leftEye.servoWrite(90);
    
    if (leftEye.getDistance() <= 20){
       if(rightEye.getDistance() >= 20){
        earthworm.turnAngle(53);
        earthworm.driveDistance(36);
        leftEye.servoWrite(143);
       if (leftEye.getDistance() >= 20){
          earthworm.turnAngle(90);
          leftEye.servoWrite(90);
          earthworm.driveDistance(48);
        }
      } else {
        earthworm.driveDistance(3);
        traveled = traveled+3;
        earthworm.updateState();
      }
    }
  }
  
  leftDrive.setLinearPower(255);
  delay(1000);
  leftDrive.setLinearPower(128);
  delay(1000);
  leftDrive.setLinearPower(64);  
  delay(1000);
  leftDrive.setLinearPower(0);
  dest = 40;
  while(true){
  }
}
