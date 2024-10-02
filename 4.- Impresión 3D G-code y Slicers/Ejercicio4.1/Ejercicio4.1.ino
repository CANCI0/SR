#include <Servo.h>

int UPPER = 520;
int LOWER = 450;

int X_pin = A0;
int Y_pin = A1;
int joystick_pin = 4;

Servo servo;
int servo_pin = 11;

/**
 * (Teleoperado4.1) Actividad 4.1: Actuador lineal teleoperado (0,15 puntos)
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

void setup() {
  servo.attach(servo_pin);
  servo.write(90);
  
  pinMode(X_pin,INPUT);
  pinMode(Y_pin,INPUT);
  pinMode(joystick_pin,INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int read = analogRead(X_pin);
  Serial.println(read);
  if(read > UPPER){
    servo.write(180);
  } else if(read < LOWER){
    servo.write(0);
  } else {
    servo.write(90);
  }
}
