#include <iostream> 
#include "Or.hpp"

// constructeur 
Or::Or(): Tresor("Or", 3, 6){}; 

// destructeur
Or::~Or(){}; 

// méthode d'affichage 
void Or::afficher() const {
    std::cout << "Or - Valeur : " << getValeurTresor()
              << ", Cout : " << getCout() << std::endl;
}