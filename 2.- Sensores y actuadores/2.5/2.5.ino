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
#include <TM1637Display.h>

// pins
int redLed = 6;
int greenLed = 7;
int foto = A5;

int trig = 11;
int echo = 10;
unsigned long millisTime = 0;
unsigned long result = 0;

const byte rows = 4;
const byte cols = 4;

bool open = false;
int entryCount = 0;

// Matriz mapping keypad
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinsRow[rows] = {2, 3, 4, 5};
byte pinsCol[cols] = {A0, A1, A2, A3};

// Contraseña
char passw[4] = {'9', '8', '7', '6'};

// Pines del KeyPad
Keypad keypad = Keypad(makeKeymap(keys), pinsRow, pinsCol, rows, cols);             

// Pines pantalla segmentos
TM1637Display display(9, 8);

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // Cerrado -> Led roja
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  // Ultrasound
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);

  // All segments on
  display.setSegments(data);

  display.clear();
}

void loop() {

 
  bool tecla = false;
  display.showNumberDec(entryCount, true);

 
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
    Serial.println(input);
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
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    delay(1000);
    digitalWrite(greenLed, HIGH);

    bool contador=true;
    while (true) { 
      int lightValue = analogRead(A5);
      int ultra = ultrasound();
      //Serial.println(lightValue);
      //Serial.println(ultra);
      if(lightValue < 350 && contador){
        
        display.showNumberDec(entryCount, false); 
        int lightValue = analogRead(A5);
        if(lightValue > 350){
          entryCount++;
          contador = false;
        }

      }
      if(lightValue < 350 && !ultra){
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
        break;
      } else if(lightValue > 500 && !ultra){
        delay(5000);
        break;
      } 
      contador = true;    
    }
    

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }
  return valid;
}

// Check if ultrasound is detecting smth at 10 cntm or less
bool ultrasound(){
  int cm = ping(trig,echo);
  Serial.print("ultasonido ");
  Serial.println(cm);
  if(cm <= 10){
    millisTime = millis();
    result = 0;
    return true;
  }
  return false;
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