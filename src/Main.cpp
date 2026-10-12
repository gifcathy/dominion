#include "Partie.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    try {
        int nombreJoueurs = 2;

        // Cartes Action choisies pour cette partie
        std::vector<std::string> cartesAction;
        cartesAction.push_back("Atelier");
        cartesAction.push_back("Bucheron");
        cartesAction.push_back("Village");

        // Creation de la partie
        Partie partie(nombreJoueurs, cartesAction);

        // Lancement de la partie
        partie.commencer();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
