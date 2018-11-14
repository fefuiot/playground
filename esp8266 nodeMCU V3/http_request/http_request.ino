
// Test of relay switching based on web socket commands
// IP for my esp: 192.168.88.255

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "IoT_Lab";
const char* password = "nopython";

StaticJsonBuffer<200> jsonBuffer;

void setup() 
{
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.println(".");
  }
  Serial.println("Connected. My IP:");
  WiFi.printDiag(Serial);
  //digitalWrite(LED, LOW);
  
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://bestiotcentral.azurewebsites.net/");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header

  JsonObject &root = jsonBuffer.createObject();
  JsonObject &sanya = root.createNestedObject("sanya");
  root["Cool?"] = true;
  sanya.set("beautifulness", "10/10");

  String toSend;

  root.printTo(Serial);
  root.printTo(toSend);
 
   int httpCode = http.POST(toSend);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 }
 else
 {
    Serial.println("Error in WiFi connection");   
 }
  delay(30000);  //Send a request every 30 seconds
}
