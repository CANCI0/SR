/**
 * Ejercicio 10.1: (IoT10.1) Red de sensores de temperatura y humedad (1 punto) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

// Configuración del sensor DHT11
int pin_sensor = 5;    // Pin donde está conectado el DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT
DHT dht(pin_sensor, DHTTYPE);

// Configuración del LED
#define LEDPIN 9       // Pin donde está conectado el LED

// Configuración de red Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 }; // Dirección MAC única
EthernetServer server(80);                           // Servidor en el puerto 80
IPAddress dnsServer(8, 8, 8, 8);
IPAddress gateway(156, 35, 98, 201);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip(156, 35, 98, 93);

// Variables para los datos del sensor
float temperature = 0.0;
float humidity = 0.0;

// Función para manejar las solicitudes HTTP
void handleClient(EthernetClient client) {
  // Leer la solicitud HTTP
  String request = client.readStringUntil('\r');
  client.flush();

  // Actualizar datos del sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.println("Temperature: " + String(temperature));
  Serial.println("Humidity: " + String(humidity));

  // Procesar las rutas
  if (request.indexOf("GET / ") >= 0) {
    // Responder con datos del sensor en formato JSON
    String json = "{";
    json += "\"temperature\": " + String(temperature) + ",";
    json += "\"humidity\": " + String(humidity) + "}";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Access-Control-Allow-Origin: *");
    client.println("Connection: close");
    client.println();
    client.println(json);
  } else if (request.indexOf("GET /led/on") >= 0) {
    // Encender LED
    digitalWrite(LEDPIN, HIGH);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("LED encendido");
  } else if (request.indexOf("GET /led/off") >= 0) {
    // Apagar LED
    digitalWrite(LEDPIN, LOW);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("LED apagado");
  } else {
    // Ruta no encontrada
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("Ruta no encontrada");
  }
}

void setup() {
  // Inicializar serial
  Serial.begin(115200);

  // Inicializar LED
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // Inicializar sensor DHT
  dht.begin();

  // Iniciar conexión Ethernet
  Serial.println("Iniciando Ethernet...");
  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  server.begin();
  Serial.print("Servidor iniciado. Dirección IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Aceptar conexiones de clientes
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Nuevo cliente conectado.");
    handleClient(client);
    delay(1); // Dar tiempo para enviar datos al cliente
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
