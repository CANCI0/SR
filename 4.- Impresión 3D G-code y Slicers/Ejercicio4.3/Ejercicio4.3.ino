#include <Servo.h>

/**
 * (Seguro4.3) Actividad 4.3: Recorrido seguro (0,2 puntos)
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
 
int UPPER = 913;
int LOWER = 400;

int X_pin = A0;
int Y_pin = A1;
int joystick_pin = 4;
int right_collision_pin = 3;
int left_collision_pin = 2;

Servo servo;
int servo_pin = 11;

void setup() {
  servo.attach(servo_pin);
  servo.write(90);
  
  pinMode(X_pin,INPUT);
  pinMode(Y_pin,INPUT);
  pinMode(right_collision_pin, INPUT);
  pinMode(left_collision_pin, INPUT);
  pinMode(joystick_pin,INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int read = analogRead(X_pin);
  
  if(digitalRead(right_collision_pin) && read > UPPER){
    servo.write(180);
  } else if(digitalRead(left_collision_pin) && read < LOWER){
    servo.write(0);
  } else {
    servo.write(90);
  }
}
