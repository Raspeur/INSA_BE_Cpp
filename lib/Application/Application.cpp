#include <iostream>
#include <Arduino.h>

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

    void CommandeManuelle(uint8_t etat_led)
    {
        if(etat_led!=0)
            allumer();
        else
            eteindre();
    }
};