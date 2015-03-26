#include <Encoder.h>
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11;
int motorR=12;
int motorL=13;
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance, newPos, oldPos; // Duration used to calculate distance
int sharpR=A0;
int sharpL=A1;
int sharpF=A2;
Encoder EncR(5, 6);
Encoder EncL(8, 9);
int moved=0;

void setup(){
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(motorR, LOW);
  digitalWrite(motorL, LOW);
  pinMode(sharpF, INPUT);
  pinMode(sharpR, INPUT);
  pinMode(sharpL, INPUT);
  Serial.begin(9600);
}

long oldPosL  = 0;
long oldPosR  = 0;

void loop(){
  if(analogRead(sharpF)>=500){
    Move(200,-200);
    Serial.println("back");
    delay(40);
  }
  else if(analogRead(sharpR)>=500){
    Move(200,10);
    Serial.println("turnR");
    delay(20);
  }
  else if(analogRead(sharpL)>=500){
    Move(10,200);
    Serial.println("turnL");
    delay(20);
  }
  else{
    Move(200,200);
    Serial.println("forward");
    delay(40);
  }
}
int Enc(Encoder enc, int oldPos){
  int moved1=moved;
  long newPos = enc.read();
  moved=newPos-oldPos;
  oldPos = newPos;
  return moved+moved1;
}
void Move(int spR, int spL){
  if (spR<0){
    digitalWrite(motorR, LOW);
  }
  else if (spR>0){
    digitalWrite(motorR,HIGH);
  }
  if (spL<0){
    digitalWrite(motorL, HIGH);
  }
  else if(spL>0){
    digitalWrite(motorL, LOW);
  }
  analogWrite(PWMA,abs(spR));
  analogWrite(PWMB,abs(spL));
}
/*int sensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
  distance = abs(duration/58.2);
  if (abs(distance) >= maximumRange || abs(distance) <= minimumRange){
 Send a negative number to computer and Turn LED ON 
 to indicate "out of range"
   //Serial.println("-1");
 }
 else {
 Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading.
  return distance;
 }
}*/
  
