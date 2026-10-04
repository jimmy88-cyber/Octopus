#include <Servo.h>

Servo servo1;

// กำหนดขา
int servo_pin = 3;
int relay1 = 6;
int relay2 = 7;

// ตัวแปรเวลา
unsigned long previousServoMillis = 0;
unsigned long previousRelayMillis = 0;

// กำหนดช่วงเวลา (หน่วยเป็นมิลลิวินาที)
unsigned long servoInterval = 10;  // 10 ms ต่อการหมุน 1 องศา

// ตัวแปรควบคุม servo
int servoPos = 0;
int servoDir = 1;  // 1 = หมุนไปข้างหน้า, -1 = หมุนกลับ

// ตัวแปรควบคุม relay
int relayState = 0;  // 0 = relay1 on, 1 = relay1 off, 2 = relay2 on, 3 = relay2 off
unsigned long relayInterval = 0;

void setup() {
  servo1.attach(servo_pin);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);

  relayInterval = 10000;  // เริ่มต้น relay1 ติด 10 วิ
}

// ================= LOOP หลัก =================
void loop() {
  unsigned long currentMillis = millis();

  // ควบคุมการหมุน servo
  if (currentMillis - previousServoMillis >= servoInterval) {
    previousServoMillis = currentMillis;
    servoTask();
  }

  // ควบคุมการเปิดสลับ relay
  if (currentMillis - previousRelayMillis >= relayInterval) {
    previousRelayMillis = currentMillis;
    relayTask();
  }
}

// ================= ฟังก์ชันควบคุม Servo =================
void servoTask() {
  servo1.write(servoPos);
  servoPos += servoDir;

  if (servoPos >= 180 || servoPos <= 0) {
    servoDir = -servoDir;  // สลับทิศทางหมุน
  }
}

// ================= ฟังก์ชันควบคุม Relay =================
void relayTask() {
  switch (relayState) {
    case 0:  // relay1 ติด 10 วิ
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      relayInterval = 10000;
      relayState = 1;
      break;

    case 1:  // relay1 ดับ 1 วิ
      digitalWrite(relay1, LOW);
      relayInterval = 0;
      relayState = 2;
      break;

    case 2:  // relay2 ติด 10 วิ
      digitalWrite(relay2, HIGH);
      digitalWrite(relay1, LOW);
      relayInterval = 10000;
      relayState = 3;
      break;

    case 3:  // relay2 ดับ 1 วิ
      digitalWrite(relay2, LOW);
      relayInterval = 0;
      relayState = 0;
      break;
  }
}
