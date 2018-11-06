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

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server is on");
}

void loop() 
{
  server.handleClient();
}

void handleLED() {                                          // If a POST request is made to URI /LED
  digitalWrite(TAPE_SIGNAL, !digitalRead(TAPE_SIGNAL));     // Change the state of the tape
  server.sendHeader("Location","/");                        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleRoot() {
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
