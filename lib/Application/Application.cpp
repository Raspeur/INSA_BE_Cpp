#include <iostream>
#include <Arduino.h>
#include <ChainableLED.h>
#include <Servo.h>

using namespace std;

// Enum for colors
enum Colors
{
  Green = 0,
  Red,
  Yellow,
  Blue,
  Purple,
  White
};

// Base class for all home automation devices
class HomeDevice {
public:
    HomeDevice(const string& _name) : name(_name), isOn(false) {}

    // Turn on the device
    virtual void turnOn() {
        cout << name.c_str();
        cout << " is on.";
        isOn = true;
    }

    // Turn off the device
    virtual void turnOff() {
        cout << name.c_str();
        cout << " is off.";
        isOn = false;
    }

    // Check if the device is on
    bool isDeviceOn() const {
        return isOn;
    }

protected:
    string name;
    bool isOn;
};

// Class for light devices
class Light : public HomeDevice{
public:
    Light(const string& name) : HomeDevice(name){}
    virtual void alexaCommand(uint8_t brightness){}
};

// Class for single LED light
class SingleLed: public Light{
    private:
        const int pin;
    public:
      SingleLed(const string& name, const int ledPin) : Light(name), pin(ledPin)
      {
        pinMode(pin, OUTPUT);
      }

        // Override turnOn method for single LED
        virtual void turnOn()
        {
            digitalWrite(pin, HIGH);
            isOn = true;
        }

        // Override turnOff method for single LED
        virtual void turnOff()
        {
            digitalWrite(pin, LOW);
            isOn = false;
        }

        // Handle Alexa command for single LED
        virtual void alexaCommand(uint8_t ledState)
        {
          if(ledState != 0)
              turnOn();
          else
              turnOff();
        }
};

// Class for RGB LED light
class RGBLed: public Light{
private:
  const uint8_t pin, clockPin;
  Colors color;
  int R, B, G;
  ChainableLED Led;

public:
  RGBLed(const string& name, const uint8_t newPin, const uint8_t clockPin) : Light(name), pin(newPin), clockPin(clockPin), Led(pin, clockPin, 1) {
    setRGB(255, 255, 255);
  }

  // Set color for RGB LED
  RGBLed& operator=(Colors newColor) {
    this->setColor(newColor);
    return *this;
  }

  // Handle Alexa command for RGB LED
  virtual void alexaCommand(uint8_t ledState)
  {
    if(ledState != 0)
        turnOn();
    else
        turnOff();
  }

  // Override turnOff method for RGB LED
  virtual void turnOff()
  {
    setRGB(0, 0, 0);
    isOn = false;
  }

  // Override turnOn method for RGB LED
  virtual void turnOn()
  {
    setRGB(R, B, G);
    isOn = true;
  }

  // Set RGB color for RGB LED
  void setRGB(int colorR, int colorG, int colorB) {
    R = colorR;
    B = colorB;
    G = colorG;
    Led.setColorRGB(0, colorR, colorG, colorB);
  }

  // Set color for RGB LED
  void setColor(Colors newColor)
  {
    color = newColor;
    switch(color)
    {
      case(Green) :  setRGB(0, 255, 0);  break;
      case(Red) :  setRGB(255, 0, 0);  break;
      case(Yellow) :  setRGB(255, 255, 0);  break;
      case(Blue) :  setRGB(0, 0, 255);  break;
      case(Purple) :  setRGB(128, 0, 128);  break;
      case(White) : setRGB(255, 255, 255);  break;
      default :  throw invalid_argument("Invalid color");  break;
    }
  }

  int getPin() const {
    return pin;
  }
};

// Class for door
class Door : public HomeDevice{
    private:
    const int doorPin;
    Servo myservo;
    public:
    Door(const string& name, const int pinP) : HomeDevice(name), doorPin(pinP)
    {
      setDoorPin(pinP);
    }

    // Open the door
    virtual void open()
    {
        myservo.write(90);
    }

    // Close the door
    virtual void close()
    {
        myservo.write(0);
    }

    // Set pin for the door
    void setDoorPin(int pin)
    {
        myservo.attach(pin);
    }

    // Handle manual command for the door
    void manualCommand(bool doorState)
    {
        if(doorState)
            open();
        else
            close();
    }
};