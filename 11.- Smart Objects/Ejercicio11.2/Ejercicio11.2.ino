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

WiFiServer servidor(80); 
IPAddress dnsServer(8, 8, 8, 8);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);

IPAddress ip(192, 168, 61, 43);

WiFiClient cliente = servidor.available();

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
boolean lastConnected = false;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  servidor.begin();
  Serial.println("Setup");
  
  Serial.println(Ethernet.localIP());

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  pinMode(sensor, INPUT);

  connect_WiFi();
}

void loop() {
  if (cliente || millis() - lastConnectionTime > updateThingSpeakInterval) {
    Serial.println("Nueva peticion");
    String peticion = "";
    float luz = analogRead(A1);
    long aux = millis();
    if (aux - lastConnectionTime > updateThingSpeakInterval) {
      updateThingSpeak("field1=" + String(luz), cliente);
      Serial.println(luz);
    }

    String tbURI = String("/talkbacks/") + number + String("/commands/execute");

    String postMessage =  String("api_key=") + apiKeyTalkBack;

    String newCommand = String();

    int x = updateLed(tbURI, postMessage, newCommand, cliente);

    if (x == 200) {
      Serial.println("checking queue...");

      Serial.print("  Latest command from queue: ");
      Serial.println(newCommand);

      if (newCommand == "encender") {
        digitalWrite(led, HIGH);
      }

      if (newCommand == "apagar") {
        digitalWrite(led, LOW);
      }

      if (newCommand == "") {
        Serial.println("  Nothing new.");
      }

    } else {
      Serial.println("Estado raro: " + x);
    }

    cliente.stop();
  }
}

void connect_WiFi() {
// Attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    if(strlen(pass) == 0 && strlen(WEPkey) == 0){
      // Connect without password (no security, no recommendad)
      status = WiFi.begin(ssid);
    }else if(strlen(pass) > 0 && strlen(WEPkey) == 0){
      // Connect to WPA/WPA2 network
      status = WiFi.begin(ssid, pass);
    }else if(strlen(WEPkeyIndex) > 0 && strlen(WEPkey) > 0){
      // Connect to WEP network
      status = WiFi.begin(ssid, pass, WEPkey);
    }else{
      Serial.println("Error with the data variables to connect to a specific network. Check ssid, pass, WEPkeyIndex, and WEPkey");
    }
    // Wait 10 seconds for connection:
    delay(10000);
  }
}
void updateThingSpeak(String tsData, WiFiClient client) {
  lastConnectionTime = millis();
  if (client.connect(thingSpeakAddress, 80)) {

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);

    // Leer la respuesta del servidor
    // while (client.available()) {
    //   String line = client.readStringUntil('\n');
    //   Serial.println(line);  // Imprime la respuesta línea por línea
    // }

    // // Verificar si el cliente sigue conectado después de recibir la respuesta
    // if (client.connected()) {
    //   Serial.println("Conectado a ThingSpeak y respuesta recibida.");
    // }

  }
}


int updateLed(String uri, String postMessage, String &response, WiFiClient client) {
  bool connectSuccess = false;
  connectSuccess = client.connect("api.thingspeak.com", 80);

  if (!connectSuccess) {
    return -301;
  }

  postMessage += "&headers=false";

  String Headers =  String("PUT ") + uri + String(" HTTP/1.1\r\n") +
                    String("Host: api.thingspeak.com\r\n") +
                    String("Content-Type: application/x-www-form-urlencoded\r\n") +
                    String("Connection: close\r\n") +
                    String("Content-Length: ") + String(postMessage.length()) +
                    String("\r\n\r\n");

  client.print(Headers);
  client.print(postMessage);

  long startWaitForResponseAt = millis();
  while (client.available() == 0 && millis() - startWaitForResponseAt < 5000) {
    delay(100);
  }

  if (client.available() == 0) {
    return -304;
  }

  if (!client.find(const_cast<char *>("HTTP/1.1"))) {
    return -303;
  }

  int status = client.parseInt();
  if (status != 200) {
    return status;
  }

  if (!client.find(const_cast<char *>("\n\r\n"))) {
    return -303;
  }

  String tempString = String(client.readString());
  response = tempString;
  //Serial.println(status);
  return status;
}