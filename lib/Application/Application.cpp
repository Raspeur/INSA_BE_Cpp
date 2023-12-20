#include <iostream>
#include <Arduino.h>
#include <ChainableLED.h>
#include <Servo.h>

using namespace std;
// prototypes
enum t_colors
{
  green = 0,
  red,
  yellow,
  blue,
  purple,
  white
};


class DispositifDomotique {
public:
    DispositifDomotique(const string& _nom) : nom(_nom), allume(false) {}

    virtual void allumer() {
        cout << nom.c_str();
        cout << "Allumé.";
        allume = true;
    }

    virtual void eteindre() {
        cout << nom.c_str();
        cout << "Éteint.";
        allume = false;
    }

    bool estAllume() const {
        return allume;
    }

protected:
    string nom;
    bool allume;
};

class Lumiere : public DispositifDomotique{
public:
    Lumiere(const string& nom) : DispositifDomotique(nom){}
    virtual void CommandeAlexa(uint8_t brigtness){}
};
class Single_Led: public Lumiere{
    private:
        const int pin;
    public:
      Single_Led(const string& nom, const int pinLed) : Lumiere(nom), pin(pinLed)
      {
        pinMode(pin, OUTPUT);
      }
        virtual void allumer()
        {
            digitalWrite(pin, (!true));
            allume = true;
        }

        virtual void eteindre()
        {
            digitalWrite(pin, (!false));
            allume = false;
        }

        virtual void CommandeAlexa(uint8_t etat_led)
        {
          if(etat_led!=0)
              allumer();
          else
              eteindre();
        }
};
class Ch_LED_RGB: public Lumiere{
private:
  const u_int8_t pin, pin_clk;
  t_colors color;
  int Red, Blue, Green;
  ChainableLED Led;

public:
  Ch_LED_RGB(const string& nom, const u_int8_t new_pin, const u_int8_t pin_clk) : Lumiere(nom), pin(new_pin), pin_clk(pin_clk), Led(pin, pin_clk, 1) {
    setRGB(255, 255, 255);
  }
  Ch_LED_RGB& operator=(t_colors new_color) {
    this->setcolor(new_color);
    return *this;
  }
  virtual void CommandeAlexa(uint8_t etat_led)
  {
    if(etat_led!=0)
        allumer();
    else
        eteindre();
  }
  virtual void eteindre()
  {
    setRGB(0, 0, 0);
    allume = false;
  }
  virtual void allumer()
  {
    setRGB(Red, Blue, Green);
    allume = false;
  }
  void setRGB(int colorR, int colorG, int colorB) {
    Red=colorR;
    Blue=colorB;
    Green = colorG;
    Led.setColorRGB(0, colorR, colorG, colorB);
  }
  void setcolor(t_colors new_color)
  {
    color = new_color;
    switch(color)
    {
      case(green) :  setRGB(0, 255, 0);  break;
      case(red) :  setRGB(255, 0, 0);  break;
      case(yellow) :  setRGB(255, 255, 0);  break;
      case(blue) :  setRGB(0, 0, 255);  break;
      case(purple) :  setRGB(128, 0, 128);  break;
      case(white) : setRGB(255, 255, 255);  break;
      default :  setRGB(255, 255, 255);  break;
    }
  }
  int getPin() const {
    return pin;
  }
};

class Porte : public DispositifDomotique{
    private:
    const int pinPorte;
    Servo myservo;
    public:
    Porte(const string& nom, const int pinPorte) : pinPorte(pinPorte), DispositifDomotique(nom){}

    virtual void ouvrir()
    {
        myservo.write(90);
    }
    virtual void fermer()
    {
        myservo.write(0);
    }

    void setPinPorte(int pin)
    {
        myservo.attach(pin);
    }

    void CommandeManuelle(bool etat_porte)
    {
        if(etat_porte)
            ouvrir();
        else
            fermer();
    }
};