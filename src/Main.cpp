#include "Partie.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    try {
        int nombreJoueurs = 2;

        // Cartes Action choisies pour cette partie
        std::vector<std::string> cartesAction;/*
        cartesAction.push_back("Atelier");
        cartesAction.push_back("Bucheron");
        cartesAction.push_back("Village");
        cartesAction.push_back("Chapelle");
        cartesAction.push_back("Festin");
        cartesAction.push_back("Laboratoire");*/
        cartesAction.push_back("Sorciere");
        cartesAction.push_back("Douves");
        cartesAction.push_back("Cave");
        cartesAction.push_back("CDC");
        cartesAction.push_back("Chancelier");
        cartesAction.push_back("Festival");
        cartesAction.push_back("Forgeron");
        cartesAction.push_back("Marche");
        cartesAction.push_back("Mine");
        cartesAction.push_back("PSG");
        cartesAction.push_back("Renovation");
        cartesAction.push_back("Voleur");

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
