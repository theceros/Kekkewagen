#include <Servo.h>
# define trigPin 7

Servo servo; 
int flame = HIGH;
long dur, dist;
int links1 = 2;
int links2 = 4;
int rechts1 = 12;
int rechts2 = 13;
int hele_draai = 2250;
int afs_sensor_links = 5;
int afs_sensor_rechts = 6;
int afs_sensor_voor = 10;
int fan = 8; 

void setup() {
  Serial.begin(9600);
  servo.attach(9);              // attaches the servo on pin 9 to the servo object
  servo.write(90);
  pinMode(3, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(links1, OUTPUT);
  pinMode(links2, OUTPUT);
  pinMode(rechts1, OUTPUT);
  pinMode(rechts2, OUTPUT);
  pinMode(fan, OUTPUT);
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
  }
  else if(speed < 0){
    digitalWrite(links1, LOW);
    digitalWrite(links2, HIGH);
  }
  else {
    digitalWrite(links1, LOW);
    digitalWrite(links2, LOW);
  }
}
void rechts(int speed) {
  
  if (speed > 0) {
    digitalWrite(rechts1, HIGH);
    digitalWrite(rechts2, LOW);
  }
  else if(speed < 0){
    digitalWrite(rechts1, LOW);
    digitalWrite(rechts2, HIGH);
  }
  else {
    digitalWrite(rechts1, LOW);
    digitalWrite(rechts2, LOW);
  }
}
int draai(int snelheid, bool plus, int begin, int end){
    if (plus == true){
      for (int i = end; i < begin; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        flame = digitalRead(3);
        if (flame == LOW){
          Serial.print(end - i);
          Serial.println(" draai 1");
          return end - i;
        }
      } 
    } else if (plus == false){
        for (int i = begin; i > end; --i){  //van 180 tot 0 graden.
          delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
          servo.write(i);
          flame = digitalRead(3);
          if (flame == LOW){
            Serial.print(begin);
            Serial.println(" draai 2");
            return begin - i;
          }
        }
  }
  return -1;
}
int zoek(){
  if (int grad = draai(15, false, 90, 0) != -1){
    Serial.print(grad);
    Serial.println(" zoek 1");
    return grad;
  }else if (int grad = draai(15, true, 180, 0) != -1){
    Serial.print(grad);
    Serial.println(" zoek 2");
    return grad;
  }else if (int grad = draai(15, false, 180, 90) != -1){
    Serial.print(grad);
    Serial.println(" zoek 3");
    return grad;
  } else{
    return -1;
  }
}

void loop() {
  int graden = zoek();
  if (graden == -1) {
    links(1);
    rechts(-1);
    delay(hele_draai*0.5);
    links(0);
    rechts(0);
    graden = zoek();
    if (graden == -1) {
      links(1);
      rechts(-1);
      delay(hele_draai*0.25);
      links(0);
      rechts(0);
      while(graden == -1){
        while(bereken(afs_sensor_voor) > 10){
          links(1);
          rechts(1);
        }
        links(0);
        rechts(0);
        delay(1000);
        links(-1);
        rechts(1);
        delay(hele_draai*0.5);
        links(0);
        rechts(0);
        graden = zoek();
      }
    }
  }
  if (graden != -1) {
    digitalWrite(fan, HIGH);
  }
}  