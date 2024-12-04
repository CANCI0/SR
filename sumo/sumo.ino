#include <Servo.h>

Servo motorIzquierdo;
Servo motorDerecho;

const int sensorBlancoIzquierdo = 2; 
const int sensorBlancoDerecho = 3;

const int sensorUltrasonicoTrig = 4; 
const int sensorUltrasonicoEcho = 5;

int distancia;

// Configuración inicial
void setup() {
  motorIzquierdo.attach(9); 
  motorDerecho.attach(8);

  pinMode(sensorBlancoIzquierdo, INPUT);
  pinMode(sensorBlancoDerecho, INPUT);
  pinMode(sensorUltrasonicoTrig, OUTPUT);
  pinMode(sensorUltrasonicoEcho, INPUT);

  Serial.begin(9600);

  delay(5000);
}

int ping(int sensorUltrasonicoTrig, int sensorUltrasonicoEcho) {
  long timeBetween, cm;
  
  digitalWrite(sensorUltrasonicoTrig, LOW);  
  delayMicroseconds(4);
  digitalWrite(sensorUltrasonicoTrig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(sensorUltrasonicoTrig, LOW);

  // Time between pulses, in ms
  timeBetween = pulseIn(sensorUltrasonicoEcho, HIGH);  

  // Distance in cm
  cm = timeBetween * 10 / 292/ 2;     
  return cm;
}

// Loop principal
void loop() {
  distancia = ping(sensorUltrasonicoTrig, sensorUltrasonicoEcho);
  int blancoIzquierdo = digitalRead(sensorBlancoIzquierdo);
  int blancoDerecho = digitalRead(sensorBlancoDerecho);

  Serial.println("IZQ: " + blancoIzquierdo);
  Serial.println("DCH: " + blancoDerecho);

  // **1. Detectar bordes (líneas blancas)**
  if (blancoIzquierdo == HIGH && blancoDerecho == LOW) {
    Serial.println("giro derecha");
    motorIzquierdo.write(180); 
    motorDerecho.write(90); 
    delay(500);               // Ajustar posición
  } else if (blancoDerecho == HIGH && blancoIzquierdo == LOW) {
    Serial.println("giro izquierda");
    motorDerecho.write(0); 
    motorIzquierdo.write(90); 
    delay(500);               // Ajustar posición
  } else if (blancoDerecho == HIGH && blancoIzquierdo == HIGH) {
    motorDerecho.write(180);
    motorIzquierdo.write(180);
    delay(1000);
  }
  
  // **3. Buscar al oponente dinámicamente**
  else {
    Serial.println("zigzag");
    static int direccion = 0;
    if (direccion % 2 == 0) {
      motorIzquierdo.write(180); // Zigzag o espiral
      motorDerecho.write(90);
    } else {
      motorIzquierdo.write(90);
      motorDerecho.write(180);
    }
    delay(200);  // Cambiar dirección cada medio segundo
    direccion++;

  }

  // **2. Detectar al oponente**
  Serial.println(distancia);
  while ((distancia >= 0 && distancia <= 40) && (blancoDerecho == LOW && blancoIzquierdo == LOW)) {
    motorIzquierdo.write(180); // Avanzar hacia el oponente
    motorDerecho.write(0);
    distancia = ping(sensorUltrasonicoTrig, sensorUltrasonicoEcho);
    Serial.println(distancia);
  } 

}
