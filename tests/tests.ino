#include <Servo.h>
#include "blite.h"


void setup() {
Serial.begin(115200);
Serial.println("\nbuildy bee test module:");
Serial.println("1. test i/o with servo module");
Serial.println("2. test inbuilt buzzer");
Serial.println("3. test motor driver");
}

void loop() {
 
if(Serial.available() != 0)  {
    char incomingData = Serial.read(); // can be -1 if read error
    Serial.print("Got input: ");
    Serial.println(incomingData);
    if (incomingData == '1') {
      Serial.println("running servo tests");
      test_io_output(); 
    } else if (incomingData == '2') {
      Serial.println("running buzzer tests");
      test_buzzer();
    } else if (incomingData == '3') {
      Serial.println("running motor tests");
      test_motor();
    }
    
 }

}


void test_io_output() {
  Servo servo1;
  Servo servo2;
  servo1.attach(io1,400,2500);
  servo2.attach(io2,400,2500);
  servo1.write(0);
  servo2.write(0);
  delay(1000);
  int count = 0;
  while (count<=5) {
    servo1.write(180);
    servo2.write(180);

    delay(1000);

    servo1.write(0);
    servo2.write(0);
    delay(1000);
    count += 1;
  }
  servo1.detach();
  servo2.detach();
  Serial.println("IO output test complete");
  
}

void test_buzzer() {
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,0);
  Serial.println("Buzzzzzz...!!!");
  digitalWrite(buzzer,1);
  delay(1000);
  digitalWrite(buzzer,0);
  Serial.println("Buzzer test complete, Press 2 again if you didn't hear the buzzer ");
}

void test_motor() {
  pinMode(m1_pin1,OUTPUT);
  pinMode(m1_pin2,OUTPUT);
  pinMode(m2_pin1,OUTPUT);
  pinMode(m2_pin2,OUTPUT);

  digitalWrite(m1_pin1,LOW);
  digitalWrite(m1_pin2,HIGH);
  digitalWrite(m2_pin1,LOW);
  digitalWrite(m2_pin2,HIGH);

  delay(2000);

  digitalWrite(m1_pin1,HIGH);
  digitalWrite(m1_pin2,LOW);
  digitalWrite(m2_pin1,HIGH);
  digitalWrite(m2_pin2,LOW);
  
  delay(2000);

  digitalWrite(m1_pin1,LOW);
  digitalWrite(m1_pin2,LOW);
  digitalWrite(m2_pin1,LOW);
  digitalWrite(m2_pin2,LOW);
  
}
