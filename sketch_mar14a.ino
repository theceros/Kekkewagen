#include <Servo.h>

Servo myservo;                  // create servo object to control a servo

void setup() {
  myservo.attach(9);              // attaches the servo on pin 9 to the servo object
}

void draai(int snelheid, bool plus, int graden){
    if (plus == true){
      for (int i = 0; i < graden; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        myservo.write(i);             //hoeveel graden de servo staat.
      } 
    }
    if (plus == false){
      for (int i = graden; i > 0; --i){  //van 180 tot 0 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        myservo.write(i);
      }
  }
}

void loop(){
  draai(5, true, 180);
  draai(5, false, 180);
}

