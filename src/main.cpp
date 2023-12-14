#include <Arduino.h>
#include <Application.h>
#include <Espalexa.h>
#include <ESP8266WiFi.h>


#define LED 2
#define DOOR D7

Single_Led myLED("led", LED);
Ch_LED_RGB RGBLed("LedRGB1", D1, D2);
Porte myDOOR("led", DOOR);

bool wifiConnected = false;
bool connectWifi();
Espalexa espalexa;


// Change this!!
const char* ssid = "Redmi Note 10 Pro";
const char* password = "totototo";



void RGB_Led_Set(uint8_t brightness, uint32_t rgb)
{
  Serial.println(brightness);
  Serial.println(rgb);
  RGBLed.setRGB((rgb >> 16) & 0xFF, rgb & 0xFF, (rgb >> 8) & 0xFF);
  RGBLed.CommandeAlexa(brightness);
}
void Single_Led_Set(uint8_t brightness)
{
  //Control the device
  Serial.println(brightness);
  myLED.CommandeAlexa(brightness);
}
void firstDoorChanged(EspalexaDevice* d)
{
    if (d == nullptr) return; //this is good practice, but not required
  //EXAMPLE
  Serial.print("A changed to ");
  if (d->getValue()){
    Serial.println("ON");
    myDOOR.CommandeManuelle(1);
  }
  else {
    Serial.println("OFF");
    myDOOR.CommandeManuelle(0);
  }


}
void setup() {
  myDOOR.setPinPorte(DOOR);
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();



  if(wifiConnected){
    // Define your devices here. 
    espalexa.addDevice("Lampe 1", Single_Led_Set); //simplest definition, default state off
    espalexa.addDevice("Color Light", RGB_Led_Set);
    espalexa.addDevice("Porte 1", firstDoorChanged, EspalexaDeviceType::onoff);
    espalexa.begin();
    
  } else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop() {
  espalexa.loop();
  delay(1);
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