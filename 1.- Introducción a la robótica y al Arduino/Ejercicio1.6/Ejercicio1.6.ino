/**
 * (Semáforo1.5) Simular el cruce de una calle con semáforos y pasos para peatones (0,25 puntos) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
 
// uo287746 - Yago Navajas Gonzalez
// uo269502 - Luis Manuel Gonzalez Baizan

int red = 2;
int green = 3;

int blue_RGB1 = 4;
int green_RGB1 = 5;
int red_RGB1 = 6;

int blue_RGB2 = 7; 
int green_RGB2 = 8; 
int red_RGB2 = 9; 

int buzzer = 10;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  pinMode(blue_RGB1, OUTPUT);
  pinMode(green_RGB1, OUTPUT);
  pinMode(red_RGB1, OUTPUT);

  pinMode(blue_RGB2, OUTPUT);
  pinMode(green_RGB2, OUTPUT);
  pinMode(red_RGB2, OUTPUT);
  
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  analogWrite(red_RGB1,LOW);
  analogWrite(green_RGB1,255);
  analogWrite(blue_RGB1,LOW);

  analogWrite(red_RGB2,255);
  analogWrite(green_RGB2,LOW);
  analogWrite(blue_RGB2,LOW);

  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  
  delay(5000);

  analogWrite(red_RGB1,255);
  analogWrite(blue_RGB1,LOW);
  analogWrite(green_RGB1,255);
  
  delay(2500);

  analogWrite(blue_RGB1,LOW);
  analogWrite(red_RGB1,255);
  analogWrite(green_RGB1,LOW);
  
  delay(2000);
  
  analogWrite(red_RGB2,LOW);
  analogWrite(green_RGB2,255);
  analogWrite(blue_RGB2,LOW);

  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);

  for(int i = 0; i < 5; i++){
    analogWrite(buzzer,500);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
  }

  analogWrite(red_RGB2,255);
  analogWrite(green_RGB2,255);
  analogWrite(blue_RGB2,LOW);

  for(int i = 0; i < 5; i++) {
    analogWrite(buzzer,500);
    digitalWrite(green,LOW);
    delay(250);
    analogWrite(buzzer,LOW);
    digitalWrite(green,HIGH);
    delay(250);
  }

  analogWrite(red_RGB2,255);
  analogWrite(green_RGB2,LOW);
  analogWrite(blue_RGB2,LOW);

  digitalWrite(green,LOW);
  digitalWrite(red,HIGH);
  
  delay(2000);
}