/**
 * (Regulador1.8) Control de luces (0,15) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

int led1 = 7;
int led2 = 9;
int led3 = 10;

int pinPotenciometro = A0;
int angle;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(pinPotenciometro, INPUT);
}

void loop() {
  angle = map(analogRead(pinPotenciometro),0,1023,0,255);
  int value;
  if(angle < 64){
    value = map(angle,0,63,0,255);
    analogWrite(led1, value);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
  } else if(angle >= 64 && angle < 128){
    value = map(angle,64,127,0,255);
    analogWrite(led1, 0);
    analogWrite(led2, value);
    analogWrite(led3, 0);
  } else if(angle >= 128 && angle < 192){
    value = map(angle,128,191,0,255);
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, value);
  } else if(angle >= 192 && angle < 255){
    value = map(angle,192,255,0,255);
    analogWrite(led1, value);
    analogWrite(led2, value);
    analogWrite(led3, value);
  }
}
