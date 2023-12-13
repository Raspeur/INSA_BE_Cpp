#include <iostream>
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
public:
    Lumiere(const string& nom) : DispositifDomotique(nom) {}

    void traiterCommandeVocale(const string& commande) {
        if (commande == "allume la lumière") {
            allumer();
        } else if (commande == "éteins la lumière") {
            eteindre();
        } else {
            cout << "Commande vocale non reconnue pour la lumière." << endl;
        }
    }
};