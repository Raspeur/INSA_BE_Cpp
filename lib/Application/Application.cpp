#include <iostream>
#include <Arduino.h>
#include <Servo.h>
using namespace std;
// prototypes



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

    //virtual void traiterCommandeVocale(const string& commande) = 0;

protected:
    string nom;
    bool allume;
};

class Lumiere : public DispositifDomotique{
    private:
    int pinLed;
    public:
        Lumiere(const string& nom, int pin) : DispositifDomotique(nom)
    {
        
    }

    virtual void allumer()
    {
        digitalWrite(pinLed, (!true));
        allume = true;
    }
    virtual void eteindre()
    {
        digitalWrite(pinLed, (!false));
        allume = false;
    }

    void setPinLed(int pin)
    {
        pinLed = pin;
        pinMode(pinLed, OUTPUT);
    }

    void CommandeManuelle(bool etat_led)
    {
        if(etat_led)
            allumer();
        else
            eteindre();
    }
};

class Porte : public DispositifDomotique{
    private:
    int pinPorte;
    Servo myservo;
    public:
        Porte(const string& nom, int pin) : DispositifDomotique(nom)
    {
        
    }

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
