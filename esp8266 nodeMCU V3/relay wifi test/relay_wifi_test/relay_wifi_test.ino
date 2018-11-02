// Test of relay switching based on web socket commands
// IP for my esp: 192.168.88.255

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define TAPE_SIGNAL 5 // D1
#define LED 2 // I don't know why, but for esp8266 gpio2 is onboard led

const char* ssid = "IoT_Lab";
const char* password = "nopython";

ESP8266WebServer server(80);

void setup() 
{
  pinMode(TAPE_SIGNAL, OUTPUT);
  pinMode(LED, OUTPUT);

  /*WiFi.softAPdisconnect();  // Making sure that WiFi works as expected
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.begin(ssid, password);
  */

  WiFi.softAP("qwe");

  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.println(".");
  }
  Serial.println("Connected. My IP:");
  Serial.println(WiFi.localIP());
  digitalWrite(LED, LOW);

  WiFi.printDiag(Serial);

  server.on("/", handleRootPath);
  server.on("/on", tapeOn);
  server.on("/off", tapeOff);
  server.begin();
  Serial.println("Server is on");
}

void loop() 
{
  server.handleClient();
}

void tapeOn()
{
  digitalWrite(TAPE_SIGNAL, LOW);
  server.send(200, "text/plain", "Tape on!");
}

void tapeOff()
{
  digitalWrite(TAPE_SIGNAL, HIGH);
  server.send(200, "text/plain", "Tape off!");
}

void handleRootPath()
{
  server.send(200, "text/plain", "Hello");
}

