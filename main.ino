#include <Servo.h>

Servo servo;  

void setup() {
  bool flame = false;
  servo.attach(9);              // attaches the servo on pin 9 to the servo object
  servo.write(90);


  delay(1000);   //starup timer
}

// void rij(int graden, int snelheid){

// }

int draai(int snelheid, bool plus, int begin, int end){
    bool flame = false;
    if (plus == true){
      for (int i = end; i < begin; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        if (flame == true){
          return i;
        }
      } 
    }
    if (plus == false){
      for (int i = begin; i > end; --i){  //van 180 tot 0 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);
        if (flame == true){
          return i;
        }
      }
    return 0;
  }
}


void loop() {
  draai(15, false, 90, 0);
  draai(15, true, 180, 0);
  draai(15, false, 180, 90);
  delay(1000);
  // if (graden != 0){
  //   rij(graden, snelheid)
  // }

}
