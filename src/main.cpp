#include <Arduino.h>
#include <Application.h>
#include <Espalexa.h>
#include <ESP8266WiFi.h>

#define LED 2
#define DOOR D7

// Create instances of SingleLed, RGBLed, and Door
SingleLed myLED("led", LED);
RGBLed myRGBLed("LedRGB1", D1, D2);
Door myDOOR("led", DOOR);

bool wifiConnected = false;
bool connectWifi();
Espalexa espalexa;

// Change this!!
const char* ssid = "Redmi Note 10 Pro";
const char* password = "totototo";

// Function to set RGB LED color and brightness
void RGB_Led_Set(uint8_t brightness, uint32_t rgb)
{
  Serial.println(brightness);
  Serial.println(rgb);
  myRGBLed.setRGB((rgb >> 16) & 0xFF, rgb & 0xFF, (rgb >> 8) & 0xFF);
  myRGBLed.alexaCommand(brightness);
}

// Function to set Single LED brightness
void Single_Led_Set(uint8_t brightness)
{
  // Control the device
  Serial.println(brightness);
  myLED.alexaCommand(brightness);
}

// Function to handle door state changes
void firstDoorChanged(EspalexaDevice* d)
{
    if (d == nullptr) return; // This is good practice, but not required
    Serial.print("A changed to ");
    if (d->getValue()){
        Serial.println("ON");
        myDOOR.open();
        myRGBLed = Colors::Green;
    }
    else {
        myRGBLed = Colors::Red;
        Serial.println("OFF");
        myDOOR.close();
        delay(3000);
        myRGBLed.turnOff();
    }
}

void setup() {
  // Put your setup code here, to run once
  Serial.begin(115200);
  // Initialize wifi connection
  wifiConnected = connectWifi();

  if(wifiConnected){
    // Define your devices here
    espalexa.addDevice("Lampe", Single_Led_Set); // Simplest definition, default state off
    espalexa.addDevice("Couleur", RGB_Led_Set);
    espalexa.addDevice("Porte", firstDoorChanged, EspalexaDeviceType::onoff);
    espalexa.begin();
  } else {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop() {
  espalexa.loop();
  delay(1);
}

// Function to connect to WiFi
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