/**
 * (Laberinto8.1) Actividad 8.1: Escapada de laberintos: mano derecha/izquierda (1 puntos)
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

int LINE = HIGH;
int NO_LINE = LOW;

int pin_servo_left = 9;
int pin_servo_right = 8;

int sensor_left_inner = 2;
int sensor_right_inner = 3;

int sensor_left_outer = 10;
int sensor_right_outer = 11;

int LEFT_FORWARD = 0;
int RIGHT_FORWARD = 180;
int STOP = 90;
int LEFT_BACKWARD = 180;
int RIGHT_BACKWARD = 0;

int initial_millis;
int actual_millis;

void setup() {
  servo_left.attach(pin_servo_left);
  servo_right.attach(pin_servo_right);

  pinMode(sensor_left_inner, INPUT);
  pinMode(sensor_right_inner, INPUT);

  pinMode(sensor_left_outer, INPUT);
  pinMode(sensor_right_outer, INPUT);

  Serial.begin(9600);
}

void loop() {
  int left_inner = digitalRead(sensor_left_inner);
  int right_inner = digitalRead(sensor_right_inner);
  int left_outer = digitalRead(sensor_left_outer);
  int right_outer = digitalRead(sensor_right_outer);

  if (left_inner == LINE && right_inner == LINE && left_outer == NO_LINE && right_outer == NO_LINE) {
    forward();
  } else if (left_inner == LINE && right_inner == NO_LINE && left_outer == NO_LINE && right_outer == NO_LINE) {
    turn_left();
  } else if (left_inner == NO_LINE && right_inner == LINE && left_outer == NO_LINE && right_outer == NO_LINE) {
    turn_right();
  } else if (left_inner == LINE && right_inner == LINE && right_outer == LINE && left_outer == NO_LINE) {
    forward();
    delay(200);
    turn_90_right();
  } else if (left_inner == NO_LINE && right_inner == NO_LINE && left_outer == NO_LINE && right_outer == NO_LINE) {
    turn_180();
    forward();
  } else if (left_inner == LINE && right_inner == LINE && left_outer == LINE && right_outer == LINE) {
    forward();
    delay(200);
    turn_90_right();
  }
}

void turn_90_right() {
  servo_right.write(RIGHT_BACKWARD);
  servo_left.write(LEFT_FORWARD);
  delay(500);
  stop();
}

void turn_180() {
  servo_right.write(RIGHT_FORWARD);
  servo_left.write(LEFT_BACKWARD);
  delay(1000);
  stop();
}

void turn_left_90() {
  servo_right.write(RIGHT_FORWARD);
  servo_left.write(LEFT_BACKWARD);
  delay(850);
  stop();
}

void forward() {
  servo_right.write(RIGHT_FORWARD);
  servo_left.write(LEFT_FORWARD);
}

void backwards() {
  servo_right.write(RIGHT_BACKWARD);
  servo_left.write(LEFT_BACKWARD);
}

void stop() {
  servo_right.write(STOP);
  servo_left.write(STOP);
}

void turn_left(){
  servo_right.write(RIGHT_FORWARD);
  servo_left.write(STOP);
}

void turn_right(){
  servo_right.write(STOP);
  servo_left.write(LEFT_FORWARD);
}