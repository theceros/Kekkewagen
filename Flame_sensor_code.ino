int servo_pin = 9 ;
int flame_sensor_pin = 5 ;
int flame_pin = HIGH ;

void setup() {

pinMode(servo_pin, OUTPUT);
pinMode(flame_sensor_pin, INPUT);
}

void loop() {
flame_pin = digitalRead(flame_sensor_pin);
if(flame_pin == LOW){
digitalWrite(servo_pin, LOW);
}
else
{
digitalWrite(servo_pin, HIGH);
}
}
