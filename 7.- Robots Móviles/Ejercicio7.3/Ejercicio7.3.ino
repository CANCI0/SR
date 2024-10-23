/**
 * (Esquiva7.3) Actividad 7.3: Esquivar obstáculos (0,3 puntos) 
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

bool line = false;
int initial_millis;
int actual_millis;

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
  if (cm <= 10) {

    dodge();
  } if (digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == LINE) {
    forward();
  } if (digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == NO_LINE) {
    line = false;
    search_line();
  } if (digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == NO_LINE) {
    turn_left(RIGHT_FORWARD);
  } if (digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == LINE) {
    turn_right(LEFT_FORWARD);
  }

}

void dodge() {
  turn_left_90();
  forward();
  delay(300);
  turn_right_90();
  forward();
  delay(300);
  turn_right_90();
  while(digitalRead(left_sensor) == NO_LINE && digitalRead(right_sensor) == NO_LINE){
    forward();
  }
  if(digitalRead(left_sensor) == LINE && digitalRead(right_sensor) == LINE){
   turn_left_90();
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
    if (!line) {
      timer = timer + 500;
      turn_right_90();
    }
  }
}

void turn_right_90() {
  turn_right(LEFT_FORWARD);
  delay(1500);
  stop();
}

void turn_right_45() {
  turn_right(LEFT_FORWARD);
  delay(750);
  stop();
}

void turn_left_90() {
  turn_left(RIGHT_FORWARD);
  delay(1500);
  stop();
}

void forward() {
  servoRight.write(RIGHT_FORWARD);
  servoLeft.write(LEFT_FORWARD);
}

void stop() {
  servoRight.write(STOP);
  servoLeft.write(STOP);
}

void turn_left(int turn) {
  servoRight.write(turn);
  servoLeft.write(STOP);
}

void turn_right(int turn) {
  servoRight.write(STOP);
  servoLeft.write(turn);
}