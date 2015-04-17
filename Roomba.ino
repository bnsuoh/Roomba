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
int moves[] = {0,0,1};

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
    Move(-200,-200);
    Serial.println("back");
  }
  else if(analogRead(sharpR)>=500){
    Move(200,0);
    Serial.println("turnR");
  }
  else if(analogRead(sharpL)>=500){
    Move(0,200);
    Serial.println("turnL");
  }
  else{
    Move(200,200);
    Serial.println("forward");
  }
  if (stuck()) {
    Move(0, -200);
    Serial.println("run");
  }
  /*oldPosR = Enc(EncR,oldPosR);
  oldPosL = Enc(EncL,oldPosL);*/
  delay(50);
  printer();
  add(Enc(EncR,oldPosR));
  int value = Enc(EncR,oldPosR);
  Serial.println(value);

}
/*int Enc(Encoder enc, int oldPos) {
  return enc.read();
}*/
void printer() {
  Serial.print("[");
  for (int i = 0; i < sizeof(moves); i++) {
    Serial.print(moves[i]);
    Serial.print(", ");
  }
  Serial.print("]");
}

void add(int j) {
  for (int i = 0; i < sizeof(moves)-1; i++) {
    moves[i] = moves[i+1];
  }
  moves[sizeof(moves)-1] = j;
}

boolean stuck() {
  for (int i = 1; i < sizeof(moves); i++) {
    if (moves[i] != moves[i-1]) {
      return false;
    }
  }
  return true;
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
    digitalWrite(motorR, HIGH);
  }
  else if (spR>0){
    digitalWrite(motorR,LOW);
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


