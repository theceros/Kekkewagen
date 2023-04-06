#include <Servo.h>
# define trigPin 7

Servo servo; 
int flame = LOW;
long dur, dist;
int links1 = 2;
int links2 = 4;
int rechts1 = 12;
int rechts2 = 13;
int hele_draai = 0;
int afs_sensor_links = 5;
int afs_sensor_rechts = 6;
int afa_sensor_voor = 10;

void setup() {
  Serial.begin(9600);
  servo.attach(9);              // attaches the servo on pin 9 to the servo object
  servo.write(90);
  pinMode(3, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(links1, OUTPUT);
  pinMode(links2, OUTPUT);
  pinMode(motorLeftPINPWM, OUTPUT);
  pinMode(rechts1, OUTPUT);
  pinMode(rechts2, OUTPUT);
  pinMode(motorRightPINPWM, OUTPUT);


  delay(1000);   //starup timer
}

int bereken(int pin){
    pinMode(pin, INPUT); 
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW); 
    dur = pulseIn(pin, HIGH); 
    dist = dur / 58.2; 
    return dist;
}

void links(int speed) {
  
  if (speed > 0) {
    digitalWrite(links1, HIGH);
    digitalWrite(links2, LOW);
    analogWrite(motorLeftPINPWM, speed);
  }
  else if(speed < 0){
    digitalWrite(links1, LOW);
    digitalWrite(links2, HIGH);
    analogWrite(motorLeftPINPWM, -speed);
  }
  else {
    digitalWrite(links1, LOW);
    digitalWrite(links2, LOW);
    analogWrite(motorLeftPINPWM, 0);
  }
}
void rechts(int speed) {
  
  if (speed > 0) {
    digitalWrite(rechts1, HIGH);
    digitalWrite(rechts2, LOW);
    analogWrite(motorRightPINPWM, speed);
  }
  else if(speed < 0){
    digitalWrite(rechts1, LOW);
    digitalWrite(rechts2, HIGH);
    analogWrite(motorRightPINPWM, -speed);
  }
  else {
    digitalWrite(rechts1, LOW);
    digitalWrite(rechts2, LOW);
    analogWrite(motorRightPINPWM, 0);
  }
}


int draai(int snelheid, bool plus, int begin, int end){
    if (plus == true){
      for (int i = end; i < begin; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        flame = digitalRead(3);
        if (flame == LOW){
          flame = HIGH;
          return begin;
        }
      } 
    } else if (plus == false){
        for (int i = begin; i > end; --i){  //van 180 tot 0 graden.
          delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
          servo.write(i);
          flame = digitalRead(3);
          if (flame == LOW){
            flame = HIGH;
            return begin;
          }
        }
  }
  return -1;
}


void zoek(){
  if (int grad = draai(15, false, 90, 0) != -1){
    Serial.println(grad);
    delay(1000);
  }else if (int grad = draai(15, true, 180, 0) != -1){
    Serial.println(grad);
    delay(1000);  
  }else if (int grad = draai(15, false, 180, 90) != -1){
    Serial.println(grad);
    delay(1000);
  }
}

void loop() {
  zoek();


}
