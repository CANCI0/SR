/**
 * (SigueLineas7.1) Actividad 7.1: Sigue líneas (0,3 puntos) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

#include <Servo.h>

Servo servo_left;
Servo servo_right;

int NO_LINE = LOW;
int LINE = HIGH;

int pin_servo_left = 8;
int pinServo_right = 9;

int left_sensor = 2;
int right_sensor = 3;

int IZQ_FORWARD = 180;
int DCHA_FORWARD = 0;
int STOP = 90;
int IZQ_BACKWARD = 0;
int DCHA_BACKWARD = 180;

void setup() {
  servo_left.attach(pin_servo_left);
  servo_right.attach(pinServo_right);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
}

void loop() {
  if(digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == LINE){
    forward();
  } else if(digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == NO_LINE){
    stop();
  } else if(digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == NO_LINE){
    turn_left();
  } else if(digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == LINE) {
    turn_right();
  }
}

void forward(){
  servo_right.write(DCHA_FORWARD);
  servo_left.write(IZQ_FORWARD);
}

void stop(){
  servo_right.write(STOP);
  servo_left.write(STOP);
}

void turn_left(){
  servo_right.write(DCHA_FORWARD);
  servo_left.write(STOP);
}

void turn_right(){
  servo_right.write(STOP);
  servo_left.write(IZQ_FORWARD);
}
