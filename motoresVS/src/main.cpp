#include <Arduino.h>

#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
const int rolePerMinute = 15;
const int X_pin = 1;
const int Y_pin = 0;
int serPos = 90;
int enA = 10;
int in1 = 11;
int in2 = 12;
String datoStr = "";
int vel = 0;

Servo myservo;
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

void setup() {
  myStepper.setSpeed(rolePerMinute); //Serial.begin(9600);
  myservo.attach(9);
  delay(50);
  myservo.write(serPos);
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
/*
  analogWrite(enA, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

*/
  
  if(Serial.available()){
    datoStr = Serial.readString();
    datoStr.trim();
    String sentido = datoStr.substring(0, 1);
    String velo = datoStr.substring(1);
    

    if(sentido.equals("A")){
    Serial.println(sentido + " " + velo);
    analogWrite(enA, velo.toInt());
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    //Serial.println("A");
    }
    else if(sentido.equals("B")){
      Serial.println(sentido + " " + velo);
      analogWrite(enA, velo.toInt());
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
  }

  

  int a = analogRead(X_pin);
  int b = analogRead(Y_pin);

  //Serial.println(String(a) + " " + String(b));
  delay(5);
  if (b < 400){
    if(serPos > 0)
      myservo.write(serPos--);
  }

  else if (b > 530){
    if(serPos < 180)
      myservo.write(serPos++);
  }



  if (a > 400 && a < 520) {
    for (int i = 2; i < 6; i++){
      digitalWrite(i, LOW);
    }
  }

  else if (a < 400){
    myStepper.setSpeed(rolePerMinute);
    myStepper.step(-30);
  }

  else if (a > 530){
    myStepper.setSpeed(rolePerMinute);
    myStepper.step(30);
  }
}