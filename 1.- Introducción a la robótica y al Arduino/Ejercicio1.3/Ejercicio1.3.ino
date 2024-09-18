int BASE_LIGHTS = 3;

int GREEN_NOTE = 37;
int RED_NOTE = 82;

int numbers[5];
int input[5];

int redButton = 2;
int greenButton = 3;

int redLed = 4;
int greenLed = 5;
int blueLed = 6;

int buzzer = 13;

int lvl = 0;

int pinForRandom = A0;

/**
 * (Zumbador1.3) Ampliar el juego de memoria con un Zumbador y LED RGB (0,3 puntos)
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
  pinMode(blueLed, OUTPUT);
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
      tone(buzzer, GREEN_NOTE, 1000);
      delay(1000);
      digitalWrite(greenLed, LOW);
    }else{
      digitalWrite(redLed, HIGH);
      tone(buzzer, RED_NOTE, 1000);
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
      tone(buzzer, GREEN_NOTE, 1000);
      delay(1000);
      digitalWrite(greenLed, LOW);
    } else if(digitalRead(redButton) == HIGH) {
      input[n++] = 0;
      digitalWrite(redLed, HIGH);
      tone(buzzer, RED_NOTE, 1000);
      delay(1000);
      digitalWrite(redLed, LOW);
    }
  }
}

void checkInput(){
  int target = BASE_LIGHTS + lvl;
  int actual = 0;
  int loseNotes[] = {330, 262, 196, 165, 220, 247, 247, 220};

  for(int i = 0 ; i < target ; i++){
    if(input[i] == numbers[i]){
      actual++;
    }
  }

  if(actual == target){
    lvl++;
  } else {
    for (int i = 0; i < sizeof(loseNotes)/sizeof(int); i++) {   
      digitalWrite(blueLed, HIGH);
      delay(1000);
      digitalWrite(blueLed, LOW);

      tone(buzzer, loseNotes[i], 100);
    }

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
  int notes[] = {262, 330, 392, 523, 659, 784 };
  if(lvl == 3){
      for (int i = 0; i < sizeof(notes)/sizeof(int); i++) {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, HIGH);
        delay(100);
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);

        tone(buzzer, notes[i], 100);
      }


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
