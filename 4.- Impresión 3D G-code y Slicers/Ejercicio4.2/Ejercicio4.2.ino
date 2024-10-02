#include <Servo.h>

int UPPER_FAST = 913;
int UPPER_SLOW = 600;
int LOWER_FAST = 400;
int LOWER_SLOW = 100;

int X_pin = A0;
int Y_pin = A1;
int joystick_pin = 4;

Servo servo;
int servo_pin = 11;

/**
 * (Teleoperado4.2) Actividad 4.2: Dos niveles de velocidad (0,15 puntos)
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

  if(read > UPPER_FAST){
    servo.write(180);
  } else if(read > UPPER_SLOW){
    servo.write(100);
  } else if(read < LOWER_SLOW){
    servo.write(0);
  } else if(read < LOWER_FAST){
    servo.write(80);
  } else {
    servo.write(90);
  }
}
