

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

int redLed = 8;
int greenLed = 9;

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

// Pines del KeyPad
Keypad keypad = Keypad(makeKeymap(keys), pinsRow, pinsCol, rows, cols);                              

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // Cerrado -> Led roja
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
}

void loop() {
  if(keypad.waitForKey() == 'A') {
    // Abierto -> Led verde
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    open = true;
  }

  if (keypad.waitForKey() == 'C' && open) {
    // Cerrado -> Led roja
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    open = false;
  }
}
