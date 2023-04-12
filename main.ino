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
int graden;
int teller1;

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
    // int teller = 0;
    if (plus == true){
      for (int i = end; i < begin; ++i){  //van 0 tot 180 graden.
        delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
        servo.write(i);             //hoeveel graden de servo staat.
        flame = digitalRead(3);
        // teller ++;
        if (flame == LOW){
          // Serial.print(teller);
          Serial.println("draai 1: ");
          Serial.println(i);
          if(i < 90){
            Serial.println((90 - i));
            return (90 - i);
          } else{
            Serial.print(i);
            return (90 - (180 - i));
          }
        }
      } 
    } else if (plus == false){
        for (int i = begin; i > end; --i){  //van 180 tot 0 graden.
          delay(snelheid);                     //snelheid van servo, in miliseconde (1000 ms = 1 seconde)
          servo.write(i);
          flame = digitalRead(3);
          // teller --;
          if (flame == LOW){
            Serial.print(begin - i);
            Serial.println("draai 2: ");
            Serial.println(i);
            if(i < 90){
              Serial.println((90 - (180 - i))* -1);
              return ((90 - i)* -1);
            } else{
              Serial.print((i)* -1);
              return ((90 - (180 - i))* -1);
            }
          }
        }
  }
  return -1;
}


int zoek(){
  if (int grad = draai(15, false, 90, 0); grad != -1){
    Serial.print(grad);
    Serial.println(" zoek 1");
    return grad;
  }else if (int grad = draai(15, true, 180, 0); grad != -1){
    Serial.print(grad);
    Serial.println(" zoek 2");
    return grad;
  }else if (int grad = draai(15, false, 180, 90); grad != -1){
    Serial.print(grad);
    Serial.println(" zoek 3");
    return grad;
  } else{
    return -1;
  }
}

void loop() {
  Serial.print("begin");
  while (flame == HIGH){
    teller1 = 0;
    Serial.println("HIGH");
    if (graden = zoek(); graden == -1 && flame == HIGH){
      Serial.println("draai 180");
      links(1);
      rechts(-1);
      delay(hele_draai*0.55);
      links(0);
      rechts(0);
      if (graden = zoek(); graden == -1 && flame == HIGH){
        Serial.println("draai 90 en rij");
        links(1);
        rechts(-1);
        delay(hele_draai*0.30);
        links(1);
        rechts(1);
        delay(1000);
        links(0);
        rechts(0);
      }
    }
    if (flame == LOW){
      Serial.print("graden: ");
      Serial.println(graden);
      if(graden < 0){
        graden = abs(graden);
        links(-1);
        rechts(1);
        servo.write(90);
        delay(graden*12.5);
        links(0);
        rechts(0);
      }else {
        rechts(-1);
        links(1);
        servo.write(90);
        delay(graden*13);
        links(0);
        rechts(0);
      }
    }
  }
  Serial.println("low");
  while (bereken(11) > 20){
    links(1);
    rechts(1);
    Serial.println("while"); 
  }
  links(0);
  rechts(0);

  if (digitalRead(3) == LOW && bereken(11) < 21){
    Serial.println("blow");
    digitalWrite(fan, HIGH);
    delay(3000);
    digitalWrite(fan, LOW); 
    flame = HIGH;
  }  
  if (teller1 > 3){
    flame = HIGH;
  }
  teller1++;

}

