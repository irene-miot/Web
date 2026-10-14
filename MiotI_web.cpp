#include <iostream>
#include <string>

class SessioUsuari {
private:
    std::string nomUsuari;
    int tempsLlimitSegons;
    bool activa;

    void tancarSessio() {
        activa = false;
    }

public:
    SessioUsuari()
        : nomUsuari("convidat"), tempsLlimitSegons(300), activa(true) {
    }

    explicit SessioUsuari(const std::string& nom)
        : nomUsuari(nom), tempsLlimitSegons(600), activa(true) {
    }

    SessioUsuari(const std::string& nom, int tempsLlimit)
        : nomUsuari(nom),
        tempsLlimitSegons(tempsLlimit <= 0 ? 60 : tempsLlimit),
        activa(true) {
    }

    ~SessioUsuari() {
        if (activa) {
            tancarSessio();
            std::cout << "[AUDITORIA] La sessió de '" << nomUsuari
                << "' s'ha tancat automàticament en sortir d'àmbit." << std::endl;
        }
    }

    std::string getNomUsuari() const {
        return nomUsuari;
    }

    bool isActiva() const {
        return activa;
    }

    void ampliarTemps(int segons) {
        if (segons > 0) {
            tempsLlimitSegons += segons;
            std::cout << "S'han afegit " << segons << " segons a la sessió de " << nomUsuari << "." << std::endl;
        }
        else {
            std::cout << "Error: Només es poden afegir valors positius de temps." << std::endl;
        }
    }
};


void executarOperacio() {
    std::cout << "Iniciant operació d'usuari" << std::endl;
    SessioUsuari sessioAdmin("Admin", 1200);
    std::cout << "Usuari: " << sessioAdmin.getNomUsuari() << "Activa: " << (sessioAdmin.isActiva() ? "Sí" : "No") << std::endl;
    sessioAdmin.ampliarTemps(300);
    std::cout << "Finalitzant operació d'usuari" << std::endl;
}

int main() {
    std::cout << "PROVA DE DESTRUCTOR AUTOMÀTIC" << std::endl;
    executarOperacio();
    std::cout << "L'operació ha acabat correctament." << std::endl;

    return 0;
}