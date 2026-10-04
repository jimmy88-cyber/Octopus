#include <Servo.h>
Servo servo1;
int servo_pin = 3;
int echo_pin = 5;
int trig_pin = 4;
int relay_pin = 6; //ไฟขาว
int relay1_pin = 7; //ไฟแดง
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(relay1_pin, OUTPUT);
  servo1.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic();
  servo();
}


void ultrasonic() {
  long duration, distance;
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.println("cm");
  delay(700);
  if 
  // (distance < 70)  
  (distance>60 && distance<12) 
  {
    Serial.println("เปิดไฟ");
    digitalWrite(relay_pin, LOW);
    digitalWrite(relay1_pin, HIGH);  //ไฟแดง
    // servo();
    delay(30000);
    digitalWrite(relay1_pin, LOW);
  } else {
    digitalWrite(relay1_pin, LOW);
    digitalWrite(relay_pin, HIGH);     //ไฟขาว
  }
}


void servo() {

  for (int i = 0; i <= 180; i ++) {
    servo1.write(i);

    delay(100);
  }




  for (int i = 180; i >= 0; i --) {
    servo1.write(i);
    delay(100);
  }
}
