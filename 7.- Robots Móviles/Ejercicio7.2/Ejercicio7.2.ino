/**
 * (BuscaLínea7.2) Actividad 7.2: Encontrar el circuito (0,3 puntos) 
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

int LEFT_FORWARD = 180;
int RIGHT_FORWARD = 0;
int STOP = 90;
int LEFT_BACKWARD = 0;
int RIGHT_BACKWARD = 180;

bool line = false;
int initial_millis;
int actual_millis;

void setup() {
  servoLeft.attach(pin_servo_left);
  servoRight.attach(pin_servo_right);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
}

void loop() {
  if (digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == LINE) {
    forward();
  } else if (digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == NO_LINE) {
    line = false;
    search_line();
  } else if (digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == NO_LINE) {
    turn_left(RIGHT_FORWARD);
  } else if (digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == LINE) {
    turn_right(LEFT_FORWARD);
  }
}

void search_line() {
  int timer = 1000;
  while (!line) {
    initial_millis = millis();
    actual_millis = millis();
    while (actual_millis - initial_millis < timer && !line) {
      servoLeft.write(LEFT_FORWARD);
      servoRight.write(RIGHT_FORWARD);
      actual_millis = millis();

      if (digitalRead(left_sensor) == LINE || digitalRead(right_sensor) == LINE) {
        line = true;
      }
    }
    if(!line){
      timer = timer + 500;
      turn_right_delay();
    }
  }
}

void turn_right_delay() {
  turn_right(LEFT_FORWARD);
  delay(1500);
}

void forward() {
  servoRight.write(RIGHT_FORWARD);
  servoLeft.write(LEFT_FORWARD);
}

void stop() {
  servoRight.write(STOP);
  servoLeft.write(STOP);
}

void turn_left(int giro) {
  servoRight.write(giro);
  servoLeft.write(STOP);
}

void turn_right(int giro) {
  servoRight.write(STOP);
  servoLeft.write(giro);
}

