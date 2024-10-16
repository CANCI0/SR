/**
 * (Regulador1.7) Control y regulador de luz (0,15) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

int led1 = 4;
int led2 = 5;
int led3 = 6;

int pinPotenciometro = A0;
int angle;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(pinPotenciometro, INPUT);
}

void loop() {
  angle = map(analogRead(pinPotenciometro),0,1023,0,180);
  if(angle < 22){
    analogWrite(led1, LOW);
    analogWrite(led2, LOW);
    analogWrite(led3, LOW);
  } else if(angle > 22 && angle < 44){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else if(angle > 44 && angle < 66){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }else if(angle > 66 && angle < 88){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  } else if(angle > 88 && angle < 110){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  } else if(angle > 110 && angle < 132){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else if(angle > 132 && angle < 154){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  } else if(angle > 154 && angle < 180){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
}
