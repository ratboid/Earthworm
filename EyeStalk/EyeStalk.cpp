#ifndef EYESTALK_CPP
#define EYESTALK_CPP

EyeStalk::EyeStalk (int usPin, int svPin){
  pingPin = usPin;
  servoPin = svPin;
  servo.attach(servoPin);
}

void EyeStalk::servoWrite(int theta){
   servo.write(theta);
}

int EyeStalk::servoRead(){
  return servo.read();
}

int EyeStalk::getDistance(){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn (pingPin, HIGH);
  return mstocm(duration);
}

long EyeStalk::mstocm (long microsecs){
  return microsecs/29/2;
}

long EyeStalk::mstoin(long microsecs){
  return microsecs/74/2;
}


#endif