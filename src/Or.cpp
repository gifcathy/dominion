#include <iostream> 
#include "Or.hpp"

// constructeur 
Or::Or(): Tresor("Or", 3, 6){}; 

// destructeur
Or::~Or(){}; 

// méthode d'affichage 
void Or::afficher() const {
    std::cout << "Or - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurTresor() << "\n"
              << "Type de carte : Trésor \n"
              << "Description : pièce ayant une valeur de 3" << std::endl;
}