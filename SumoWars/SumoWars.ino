/**
 * Sumo Wars
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int LINE = HIGH;
int NO_LINE = LOW;

int pin_servo_left = 8;
int pin_servo_right = 9;

int left_sensor = 2;
int right_sensor = 3;

int trigger = 4;
int echo = 5;

int LEFT_FORWARD = 180;
int RIGHT_FORWARD = 0;
int STOP = 90;
int LEFT_BACKWARD = 0;
int RIGHT_BACKWARD = 180;

void setup() {
  servoLeft.attach(pin_servo_left);
  servoRight.attach(pin_servo_right);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

void loop() {
  int cm = ping(trigger, echo);
  Serial.println(cm);
  if (cm <= 50) {
    forward();
  } else {
    garen();
  }
}

int ping(int trigger_pin, int echo_pin) {
  long duration, distance_cm;

  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  distance_cm = duration * 10 / 292 / 2;
  return distance_cm;
}

void forward() {
  servoRight.write(RIGHT_FORWARD);
  servoLeft.write(LEFT_FORWARD);
}

void garen(int turn) {
  servoRight.write(RIGHT_FORWARD);
  servoLeft.write(LEFT_BACKWARD);
}