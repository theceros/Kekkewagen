int links1 = 2;
int links2 = 4;
int rechts1 = 12;
int rechts2 = 13;

int hele_draai = 2250;

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

void setup() {
  pinMode(links1, OUTPUT);
  pinMode(links2, OUTPUT);
  pinMode(rechts1, OUTPUT);
  pinMode(rechts2, OUTPUT);
}

void loop() {
  // stop
  links(0);
  rechts(0);
  delay(1000);

  // rechtdoor
  links(1);
  rechts(1);
  delay(1000);

    // stop
  links(0);
  rechts(0);
  delay(1000);

  // links
  links(-1);
  rechts(1);
  delay(hele_draai*0.5);

  // stop
  links(0);
  rechts(0);
  delay(1000);

  // //rechts
  // links(1);
  // rechts(-1);
  // delay(hele_draai);
  
}
