#include <iostream>
#include "Cuivre.hpp"

// constructeur 
Cuivre::Cuivre() : Tresor("Cuivre", 1, 0){}; 

// destructeur 
Cuivre::~Cuivre(){}; 

// méthode d'affichage 
void Cuivre::afficher() const {
    std::cout << "Cuivre - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurTresor() << "\n"
              << "Type de carte : Trésor \n"
              << "Description : pièce ayant une valeur de 1" << std::endl;
}