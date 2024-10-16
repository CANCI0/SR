/**
 * (Semáforo1.4) Simular el cruce de una calle con semáforos (0,25 puntos)
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
 
int red1 = 2;
int yellow1 = 3;
int green1 = 4;

int red2 = 5;
int yellow2 = 6; 
int green2 = 7;

void setup() {
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);

  digitalWrite(green1,HIGH);
  digitalWrite(yellow1,LOW);
  digitalWrite(red1,LOW);
  
  digitalWrite(green2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(red2,HIGH);
}

void loop() {
  digitalWrite(red1,LOW);
  digitalWrite(green1,HIGH);
  
  delay(5000);
  digitalWrite(green1,LOW);
  digitalWrite(yellow1,HIGH);
  delay(1500);
  digitalWrite(yellow1,LOW);
  digitalWrite(red1,HIGH);
  delay(2000);
  
  digitalWrite(green2,HIGH);
  digitalWrite(red2,LOW);
  delay(5000);
  digitalWrite(green2,LOW);
  digitalWrite(yellow2,HIGH);
  delay(1500);
  digitalWrite(yellow2,LOW);
  digitalWrite(red2,HIGH);
  delay(2000);
}