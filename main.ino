#include <servo.h>

Servo servo;  

void setup() {
  servo.attach(9);              // attaches the servo on pin 9 to the servo object
}

bool flame(){
  if (flame == true){
    return true;
  }

}

void rij(int graden, int snelheid){

}

int draai(int snelheid, bool plus, int graden){
    if (plus == true){
      for (int i = 0; i < graden; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        if (flame() == true){
          return graden;
        }
      } 
    }
    if (plus == false){
      for (int i = graden; i > 0; --i){  //van 180 tot 0 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);
        if (flame() == true){
          return graden;
        }
      }
    return 0;
  }
}


void loop() {
  int graden = draai(15, true, 180);
  if (graden != 0){
    rij(graden, snelheid)
  }

}
