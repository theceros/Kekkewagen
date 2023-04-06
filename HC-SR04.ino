# define trigPin 6 // Trigger Pin 
long dur, dist; // Duration used to calculate distance 
void setup() 
{ 
    Serial.begin(9600); 
    pinMode(trigPin, OUTPUT); 
} 

void bereken(int pin){
    pinMode(pin, INPUT); 
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW); 
    dur = pulseIn(pin, HIGH); 
    dist = dur / 58.2; 
    Serial.println(dist);
    delay(50);
}

void loop() 
{ 
    bereken(10);
    delay(50);
}