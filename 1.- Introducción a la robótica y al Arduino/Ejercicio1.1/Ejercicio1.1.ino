int led1 = 2;
int led2 = 3;
int led3 = 4;
int button = 5;
int buttonState= 0;
int randomx = 0;
int pinForRandom = A0;
int pushed = 0;

/**
 * (Dado1.1) Actividad 1.1: Dado electrónico (0,15 puntos)
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(button, INPUT);
  
  randomSeed(analogRead(pinForRandom));
}

void loop() {
  int read = digitalRead(button);

  if(read == HIGH && pushed == 0){
    pushed = 1;
    randomx = random(1,4);
    Serial.print(randomx);
    
    switch(randomx){
      case 1:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        break;
      case 2:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        break;
      case 3:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        break;
    }
  }else if(read == LOW && pushed == 1){
    pushed = 0;
  }
}
