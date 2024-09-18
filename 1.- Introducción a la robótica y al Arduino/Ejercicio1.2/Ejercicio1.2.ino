int BASE_LIGHTS = 3;

int numbers[5];
int input[5];

int redButton = 2;
int greenButton = 3;

int redLed = 4;
int greenLed = 5;

int lvl = 0;

int pinForRandom = A0;

/**
 * (Memoria1.2) Actividad 1.2: Juego de memoria (0,4 puntos)
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redButton, OUTPUT);
  pinMode(greenButton, OUTPUT);
  
  randomSeed(analogRead(pinForRandom));

  generateNumbers();

  Serial.begin(9600);
}

// 0 es rojo, 1 es verde
void showSequence(){
  for(int i = 0 ; i < BASE_LIGHTS + lvl ; i++){
    delay(1000);
    if(numbers[i]){
      digitalWrite(greenLed, HIGH);
      delay(1000);
      digitalWrite(greenLed, LOW);
    }else{
      digitalWrite(redLed, HIGH);
      delay(1000);
      digitalWrite(redLed, LOW);
    }
  }
}

void userInput(){
  int n = 0;                                   //Indica la posición del input que se da
  while(n < BASE_LIGHTS + lvl){
    if(digitalRead(greenButton) == HIGH){
      input[n++] = 1;
      digitalWrite(greenLed, HIGH);
      delay(1000);
      digitalWrite(greenLed, LOW);
    } else if(digitalRead(redButton) == HIGH) {
      input[n++] = 0;
      digitalWrite(redLed, HIGH);
      delay(1000);
      digitalWrite(redLed, LOW);
    }
  }
}

void checkInput(){
  int target = BASE_LIGHTS + lvl;
  int actual = 0;

  for(int i = 0 ; i < target ; i++){
    if(input[i] == numbers[i]){
      actual++;
    }
  }

  if(actual == target){
    lvl++;
  } else {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);

    lvl = 0;
    generateNumbers();
  }
}

void generateNumbers(){
  for(int i = 0 ; i < 5 ; i++){
    numbers[i] = random(2);
  }
}

void checkEndgame(){
  if(lvl == 3){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);

    // Vuelve a empezar
    generateNumbers();
    lvl = 0;
  }
}

void loop() {
  showSequence();

  userInput();

  checkInput();

  checkEndgame();
}
