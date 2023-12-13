#include <Arduino.h>
#include <Application.h>
#include <ESP8266WiFi.h>

#define LED 2

Lumiere myLED("led");
bool wifiConnected = false;
bool connectWifi();

// Change this!!
const char* ssid = "Redmi Note 10 Pro";
const char* password = "totototo";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (wifiConnected)
  {
    Serial.println("LED is on");
  }
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(1000);
}

boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}