/*
  Ejercicio 2.3 - Contraseña (0,20 puntos)
  *****************************************************************************
  GRUPO 5:
   - Olga Alonso Grela      UO288066
   - Pablo Pérez Saaverdra  UO288816
   - Martín Cancio Barrera  UO287561
  *****************************************************************************
*/
#include <Keypad.h>

// pins
int redLed = 8;
int greenLed = 9;

int trig = 11;
int echo = 10;
unsigned long millisTime = 0;
unsigned long result = 0;

const byte rows = 4;
const byte cols = 4;

bool open = false;

// Matriz mapping keypad
char keys[rows][cols] = {{'1','2','3','A'},
                          {'4','5','6','B'},
                          {'7','8','9','C'},
                          {'*','0','#','D'}};

byte pinsRow[rows] = {2, 3, 4, 5};
byte pinsCol[cols] = {A0, A1, A2, A3};

// Contraseña
char passw[4] = {'9', '8', '7', '6'};

// Pines del KeyPad
Keypad keypad = Keypad(makeKeymap(keys), pinsRow, pinsCol, rows, cols);                              

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // Cerrado -> Led roja
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  // Ultrasound
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  
  if(isPassword()) {
    open = true;
  }

  if (keypad.waitForKey() == 'C' && open) {
    // Cerrado -> Led roja
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    open = false;
  }
}

bool isPassword(){
  char input;
  bool valid = true;
  for(int i = 0; i < 4;i++){
    input = keypad.waitForKey();
    if(input != passw[i]){
      valid = false;
    }
  }
   if(!valid){
    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    delay(500);
    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    delay(500);
    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    delay(500);
    digitalWrite(redLed, HIGH);
  }else{
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    delay(1000);
    digitalWrite(greenLed, HIGH);
    delay(5000);
    while (ultrasound()){
      delay(5000);
    }
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }
  return valid;
}

// Check if ultrasound is detecting smth at 10 cntm or less
bool ultrasound(){
  int cm = ping(trig,echo);
  Serial.print(cm);
  if(cm <= 10){
    millisTime = millis();
    result = 0;
  }
}

int ping(int trig, int echo) {
  long timeBetween, cm;
  
  digitalWrite(trig, LOW);  
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Time between pulses, in ms
  timeBetween = pulseIn(echo, HIGH);  

  // Distance in cm
  cm = timeBetween * 10 / 292/ 2;     
  return cm;
}
