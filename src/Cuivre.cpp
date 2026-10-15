#include <iostream>
#include "Cuivre.hpp"

// constructeur 
Cuivre::Cuivre() : Tresor("Cuivre", 1, 0){}; 

// destructeur 
Cuivre::~Cuivre(){}; 

void Cuivre::afficher() const {
    std::cout << "Cuivre - Valeur : " << getValeurTresor()
              << ", Cout : " << getCout() << std::endl;
}