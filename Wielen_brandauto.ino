int links1 = 10;
int links2 = 11;
int rechts1 = 12;
int rechts2 = 13;
int motorLeftPINPWM = 5;
int motorRightPINPWM = 6;

int hele_draai = 0;

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

void setup() {
  pinMode(links1, OUTPUT);
  pinMode(links2, OUTPUT);
  pinMode(motorLeftPINPWM, OUTPUT);
  pinMode(rechts1, OUTPUT);
  pinMode(rechts2, OUTPUT);
  pinMode(motorRightPINPWM, OUTPUT);
}

void loop() {

  // rechtdoor
  links(255);
  rechts(255);
  delay(500);

  // links
  links(-128);
  rechts(128);
  delay(hele_draai * percentage_draai);

  //rechts
  links(128);
  rechts(-128);
  delay(hele_draai * percentage_draai);
  
}
