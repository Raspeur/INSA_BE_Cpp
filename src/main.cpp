#include <Arduino.h>
#include <Application.h>
#include <Espalexa.h>
#include <ESP8266WiFi.h>


#define LED 2

Lumiere myLED("led", LED);

bool wifiConnected = false;
bool connectWifi();
Espalexa espalexa;
EspalexaDevice* device;

// Change this!!
const char* ssid = "Redmi Note 10 Pro";
const char* password = "totototo";



void firstLightChanged(uint8_t brightness);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myLED.setPinLed(LED);
  // Initialise wifi connection
  wifiConnected = connectWifi();

  if(wifiConnected){
    // Define your devices here. 
    device = new EspalexaDevice("Lampe 1", firstLightChanged); 
    espalexa.addDevice(device); //simplest definition, default state off

    espalexa.begin();
    
  } else
  {
    while (1) {
      cout <<"Cannot connect to WiFi. Please check data and reset the ESP.";
      delay(2500);
    }
  }
}

void loop() {
  espalexa.loop();
  delay(1);
}

void firstLightChanged(uint8_t brightness)
{
  Serial.println(brightness);
  //Control the device
  myLED.CommandeManuelle(brightness);
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