/**
 * Ejercicio 11.2: (ThingSpeak11.2) Hola Mundo en ThingSpeak (0,5 Punto) 
 *********************************************************
 * GRUPO 5:
 *    -Martín Cancio Barrera  UO287561
 *    -Olga Alonso Grela      UO288066
 *    -Pablo Pérez Saavedra   UO288816
 *********************************************************
 */
#include <SPI.h>
#include <Ethernet.h>
#include <WiFiNINA.h>

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x05};

char ssid[] = "realme";
char pass[] = "wcpijedy"; 
char WEPkeyIndex[] = ""; 
char WEPkey[] = "";
int keyIndex = 0;
int status = WL_IDLE_STATUS; 
int TURN_ON = 1;
int TURN_OFF;

WiFiServer servidor(80); 
IPAddress dnsServer(8, 8, 8, 8);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);

IPAddress ip(192, 168, 61, 43);

WiFiClient cliente;

int sensor = A1;
int led = 9;

String apiKey = "LOD4UUL7CKG2EE80";
String apiKeyTalkBack = "7UPT27V8PN39LEMU";
String channelID = "2755449";
String fieldID = "sensor";
String number = "53609";

const int updateThingSpeakInterval = 20 * 1000;

char thingSpeakAddress[] = "api.thingspeak.com";

long lastConnectionTime = 0;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  servidor.begin();
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  pinMode(sensor, INPUT);

  connect_WiFi();
}

void loop() {
  if (cliente || millis() - lastConnectionTime > updateThingSpeakInterval) {
    float luz = analogRead(sensor);
    long aux = millis();
    
    if (aux - lastConnectionTime > updateThingSpeakInterval) {
      updateThingSpeak("field1=" + String(luz));
      Serial.println("Sensor de luz: " + String(luz));
    }

    String tbURI = String("/talkbacks/") + String(number) + String("/commands/execute");
  
    // Crear el cuerpo del mensaje para el POST
    String postMessage = String("api_key=") + String(apiKeyTalkBack);                      
                        
    // Crear una cadena para cualquier comando recibido
    String newCommand = String();

    // Realizar el POST a ThingSpeak
    int x = httpPOST(tbURI, postMessage, newCommand);
    
    if (x == 200) {
      Serial.println("Revisando cola de comandos...");
      if (newCommand == "encender") {
          Serial.println("Encendiendo led");
          digitalWrite(led, HIGH);
      } else if (newCommand == "apagar") {
          Serial.println("Apagando led");
          digitalWrite(led, LOW);
      } else {
          Serial.println("Comando desconocido: " + newCommand);
      }
    } else {
        Serial.println("Error al revisar la cola. Código HTTP: " + String(x));
    }
  }
}

void connect_WiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Intentando conectar con SSID: ");
    Serial.println(ssid);
    
    if (strlen(pass) == 0 && strlen(WEPkey) == 0) {
      status = WiFi.begin(ssid);
    } else if (strlen(pass) > 0 && strlen(WEPkey) == 0) {
      status = WiFi.begin(ssid, pass);
    } else if (strlen(WEPkeyIndex) > 0 && strlen(WEPkey) > 0) {
      status = WiFi.begin(ssid, pass, WEPkey);
    } else {
      Serial.println("Error en los datos de conexión. Verifica SSID, pass, WEPkeyIndex y WEPkey.");
    }
    
    delay(10000); // Esperar 10 segundos
  }
}

void updateThingSpeak(String tsData) {
  lastConnectionTime = millis();
  if (cliente.connect(thingSpeakAddress, 80)) {
    cliente.print("POST /update HTTP/1.1\n");
    cliente.print("Host: api.thingspeak.com\n");
    cliente.print("Connection: close\n");
    cliente.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    cliente.print("Content-Type: application/x-www-form-urlencoded\n");
    cliente.print("Content-Length: ");
    cliente.print(tsData.length());
    cliente.print("\n\n");
    cliente.print(tsData);
  }
}

int httpPOST(String uri, String postMessage, String &response) {
  WiFiClient client;
  bool connectSuccess = client.connect("api.thingspeak.com", 80);

  if (!connectSuccess) {
    return -301; // Error al conectar
  }

  String Headers = String("POST ") + uri + " HTTP/1.1\r\n" +
                   "Host: api.thingspeak.com\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n" +
                   "Connection: close\r\n" +
                   "Content-Length: " + String(postMessage.length()) + "\r\n\r\n";

  client.print(Headers);
  client.print(postMessage);

  long startWaitForResponseAt = millis();
  while (client.available() == 0 && millis() - startWaitForResponseAt < 5000) {
    delay(100);
  }

  if (client.available() == 0) {
    return -304; // Timeout
  }

  if (!client.find("HTTP/1.1")) {
    return -303; // Respuesta no válida
  }

  int status = client.parseInt();
  if (status != 200) {
    return status; // Error HTTP
  }

  if (!client.find("\n\r\n")) {
    return -303; // Sin cuerpo en la respuesta
  }

  response = client.readString();
  return status; // 200 OK
}
