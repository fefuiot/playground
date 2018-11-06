
// Test of relay switching based on web socket commands
// IP for my esp: 192.168.88.255

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define TAPE_SIGNAL 5 // D1
#define SENSOR_PIN A0 // A0 (oh really?)
#define LED 2 // I don't know why, but for esp8266 gpio2 is onboard led

const char* ssid = "IoT_Lab";
const char* password = "nopython";

ESP8266WebServer server(80);

bool noLight = false;
bool isOn = false;

int newtime = 0, lasttime = 0;
int newvalue = 0, lastvalue = 0;

const char html[] PROGMEM = R"=====(
<!DOCTYPE html><html> 
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
            <link rel="icon" href="data:,">
                <style>
                    html
                    {
                        font-family: Helvetica;
                        display: inline-block;
                        margin: 0px auto;
                        text-align: center; 
                    }
                    .button 
                    { 
                        background-color: #195B6A; 
                        border: none; 
                        color: white; 
                        padding: 16px 40px; 
                        text-decoration: none;
                        font-size: 30px;
                        margin: 2px; 
                        cursor: pointer;
                    }
                    .button2 
                    {
                        background-color: #77878A;
                    }
                </style>
    </head>
    <body>
        <h1>ESP8266 Web Server</h1>
        <p>LED Tape</p>
        <form method="POST" action="/tape"><button class="button">Toggle</button></form>
    </body>
</html>
)=====";

void setup() 
{
  pinMode(TAPE_SIGNAL, OUTPUT);
  pinMode(LED, OUTPUT);
  
  WiFi.begin(ssid, password);

  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.println(".");
  }
  Serial.println("Connected. My IP:");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);
  digitalWrite(LED, LOW);
  
  server.on("/", handleRootPath);
  server.on("/tape", handleToggleButton);
  server.begin();
  Serial.println("Server is on");
  handleLight();
}

void loop() 
{
  newtime = millis();
  server.handleClient();
  if ((newtime - lasttime > 5000) || lasttime == 0)
  {
    if (analogRead(SENSOR_PIN) >= 300) {
      lastvalue = newvalue; 
      noLight = true;
    }
    else
      noLight = false;
    
    handleLight();
    lasttime = newtime;
  }
  
}

void handleRootPath()
{
  String s = html;
  server.send(200, "text/html", html); 
}

void handleToggleButton() {
  isOn = !isOn;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLight()
{
  if (isOn && noLight)
    digitalWrite(TAPE_SIGNAL, LOW);
  else
    digitalWrite(TAPE_SIGNAL, HIGH);
}
