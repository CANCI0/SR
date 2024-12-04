#include <WiFi.h>       // Biblioteca para Wi-Fi
#include <DHT.h>        // Biblioteca para el sensor DHT

// Configuración del sensor DHT11
int pin_sensor = 5;    // Pin donde está conectado el DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT
DHT dht(pin_sensor, DHTTYPE);

// Configuración del LED
#define LEDPIN 9       // Pin donde está conectado el LED

// Configuración de red Wi-Fi
const char* ssid = "realme";           // Nombre de la red Wi-Fi
const char* password = "wcpijedy";     // Contraseña de la red Wi-Fi
WiFiServer server(80);                  // Servidor en el puerto 80

// Variables para los datos del sensor
float temperature = 0.0;
float humidity = 0.0;

int status = WL_IDLE_STATUS;

// Función para manejar las solicitudes HTTP
void handleClient(WiFiClient client) {
  // Leer la solicitud HTTP
  String request = client.readStringUntil('\r');
  client.flush();

  // Actualizar datos del sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Comprobar si los datos son válidos
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error al leer del sensor DHT");
    temperature = 0;
    humidity = 0;
  }

  // Procesar las rutas
  if (request.indexOf("GET /data ") >= 0) {
    // Responder con datos del sensor en formato JSON
    Serial.println("Temperatura: " + String(temperature));
    Serial.println("Humedad: " + String(humidity));

    String json = "{";
    json += "\"temperature\": " + String(temperature) + ",";
    json += "\"humidity\": " + String(humidity) + "}";
    
    client.println("HTTP/1.1 200 OK");
    client.println("Access-Control-Allow-Origin: *");
    client.println("Access-Control-Allow-Methods: GET, POST, OPTIONS");
    client.println("Access-Control-Allow-Headers: Content-Type");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();  // Línea en blanco para finalizar encabezados
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

  // Cerrar la conexión
  client.stop();
}

void setup() {
  // Inicializar serial
  Serial.begin(9600);

  // Inicializar LED
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // Inicializar sensor DHT
  dht.begin();

  // Conexión a la red Wi-Fi
  Serial.println("Conectando a Wi-Fi...");
  connect_WiFi();
  Serial.println("\nConexión Wi-Fi establecida.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Iniciar servidor
  server.begin();
  Serial.println("Servidor iniciado.");
}

void connect_WiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Conectando a Wi-Fi...");
    status = WiFi.begin(ssid, password);
    delay(10000); // Esperar 10 segundos
  }
  Serial.println("\nConexión Wi-Fi establecida.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aceptar conexiones de clientes
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo cliente conectado.");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    handleClient(client);
    delay(1); // Dar tiempo para enviar datos al cliente
    Serial.println("Cliente desconectado.");
  }
}
