#include <ESP8266WiFi.h> // Usa ESP32WiFi.h si es un ESP32
#include <ESP8266WebServer.h> // Usa WebServer.h si es un ESP32
#include <DHT.h>

// Configuración del sensor DHT11
#define DHTPIN D4       // Pin donde está conectado el DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Configuración del LED
#define LEDPIN D2       // Pin donde está conectado el LED

// Configuración de red Wi-Fi
const char* ssid = "TuSSID";            // Reemplaza con tu SSID
const char* password = "TuPassword";    // Reemplaza con tu contraseña

// Crear servidor web
ESP8266WebServer server(80);

// Variables para los datos del sensor
float temperature = 0.0;
float humidity = 0.0;

// Función para manejar la raíz
void handleRoot() {
  // Actualizar datos del sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Construir respuesta JSON
  String json = "{";
  json += "\"temperature\": " + String(temperature) + ",";
  json += "\"humidity\": " + String(humidity) + "}";
  
  // Enviar respuesta
  server.send(200, "application/json", json);
}

// Función para manejar el encendido del LED
void handleLEDOn() {
  digitalWrite(LEDPIN, HIGH);
  server.send(200, "text/plain", "LED encendido");
}

// Función para manejar el apagado del LED
void handleLEDOff() {
  digitalWrite(LEDPIN, LOW);
  server.send(200, "text/plain", "LED apagado");
}

void setup() {
  // Inicializar serial
  Serial.begin(115200);

  // Inicializar LED
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // Inicializar sensor DHT
  dht.begin();

  // Conectar a Wi-Fi
  Serial.print("Conectando a Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado a Wi-Fi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Configurar rutas del servidor
  server.on("/", handleRoot);           // Ruta para datos del sensor
  server.on("/led/on", handleLEDOn);    // Ruta para encender LED
  server.on("/led/off", handleLEDOff);  // Ruta para apagar LED

  // Iniciar servidor
  server.begin();
  Serial.println("Servidor iniciado.");
}

void loop() {
  // Manejar solicitudes HTTP
  server.handleClient();
}
