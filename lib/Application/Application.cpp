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

    virtual void traiterCommandeVocale(const string& commande) = 0;

protected:
    string nom;
    bool allume;
};

class Lumiere : public DispositifDomotique {
private:
    int pinLed;
public:
    Lumiere(const string& nom) : DispositifDomotique(nom) {}

    virtual void allumer()
    {
        digitalWrite(pinLed, 1);
    }
    virtual void eteindre()
    {
        digitalWrite(pinLed, 0);
    }

    void setPinLed(int pin)
    {
        pinLed = pin;
        pinMode(pin, OUTPUT);
    }

    void traiterCommandeVocale(const string& commande) {
        if (commande == "allume la lumière") {
            allumer();
        } else if (commande == "éteins la lumière") {
            eteindre();
        } else {
            cout << "Commande vocale non compatible pour la lumière." << endl;
        }
    }

    void CommandeManuelle(bool etat_led)
    {
        if(etat_led)
            allumer();
        else
            eteindre();
    }
};