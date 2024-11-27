/*
  Contador2.5 Apertura y cierre automático con contador de entradas (0,35 puntos) 
  *****************************************************************************
  GRUPO 5:
   - Olga Alonso Grela      UO288066
   - Pablo Pérez Saaverdra  UO288816
   - Martín Cancio Barrera  UO287561
  *****************************************************************************
*/

#include <Keypad.h>

int ledRojo = 7;
int ledVerde = 8;

const byte filas = 4;
const byte columnas = 4;
char keys[filas][columnas] = {{'1','2','3','A'},
                              {'4','5','6','B'},
                              {'7','8','9','C'},
                              {'*','0','#','D'}};
byte pinesFila[filas] = {2, 3, 4, 5};
byte pinesColumna[columnas] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), pinesFila, pinesColumna, filas, columnas);

unsigned long milis = 0;
unsigned long milis5000 = 0;
unsigned long resultTime = 0;

const byte longitudPass = 4; 
char password[longitudPass] = {'9','8','7','6'};  

int trig = 10;
int echo = 11;

int fotorresistor = A5;
int clk7Seg = 9;
int d10Seg = 12;

int gente = 0;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(fotorresistor,INPUT);

  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);
  Serial.begin(9600);
}

void loop() {
  if(checkPass() || detectorLuz()){
    digitalWrite(ledVerde, LOW);
    delay(1000);
    digitalWrite(ledRojo, HIGH);

    milis = millis();

    while(resultTime < 5000){
      if(!detectorUltrasonidosYLuz() && keypad.getKey() == 'C'){      
          break;
      }
      milis5000 = millis();
      resultTime = milis5000-milis;
      //detectorUltrasonidosYLuz();
      
    }
    
    resultTime = 0;
    
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
  }
}

bool checkPass(){
  char digit;
  bool correct = true;
  for(int i = 0; i < longitudPass; i++){
    digit = keypad.waitForKey();
    if(digit != password[i]){
      correct = false;
    }
  }

  if(!correct){
    digitalWrite(ledVerde, HIGH);
    delay(500);
    digitalWrite(ledVerde, LOW);
    delay(500);
    digitalWrite(ledVerde, HIGH);
    delay(500);
    digitalWrite(ledVerde, LOW);
    delay(500);
    digitalWrite(ledVerde, HIGH);
    delay(500);
    digitalWrite(ledVerde, LOW);
    delay(500);
    digitalWrite(ledVerde, HIGH);
    return correct;
  }
  return correct;
}

bool detectorUltrasonidosYLuz(){
  int cm = ping(trig,echo);
  if(cm <= 10 || analogRead(fotorresistor) < 200){
    milis = millis();
    resultTime = 0;
    return true;
  }
  return false;
}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}

bool detectorLuz(){
  if(analogRead(fotorresistor) < 200){
    return true;
  }
  return false;
}