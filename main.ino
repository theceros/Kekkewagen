#include <Servo.h>
# define trigPin 6

Servo servo; 
int flame = LOW;
long dur, dist;

void setup() {
  Serial.begin(9600);
  servo.attach(9);              // attaches the servo on pin 9 to the servo object
  servo.write(90);
  pinMode(5, INPUT);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT); 


  delay(1000);   //starup timer
}

// void rij(int graden, int snelheid){

// }

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


int draai(int snelheid, bool plus, int begin, int end){
    if (plus == true){
      for (int i = end; i < begin; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        flame = digitalRead(5);
        if (flame == LOW){
          flame = HIGH;
          return begin;
        }
      } 
    } else if (plus == false){
        for (int i = begin; i > end; --i){  //van 180 tot 0 graden.
          delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
          servo.write(i);
          flame = digitalRead(5);
          if (flame == LOW){
            flame = HIGH;
            return begin;
          }
        }
  }
  return -1;
}


void loop() {
  if (int grad = draai(15, false, 90, 0) != -1){
    Serial.println(grad);
    digitalWrite(13, HIGH);
    delay(1000);
  }else if (int grad = draai(15, true, 180, 0) != -1){
    Serial.println(grad);
    digitalWrite(13, HIGH);
    delay(1000);  
  }else if (int grad = draai(15, false, 180, 90) != -1){
    Serial.println(grad);
    digitalWrite(13, HIGH);
    delay(1000);
  }
  digitalWrite(13, LOW);
  // if (graden != 0){
  //   rij(graden, snelheid)
  // }

}
