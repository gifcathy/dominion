#include <iostream>
#include "Laboratoire.hpp"

// constructeur 
Laboratoire::Laboratoire() : ActionActionAttaque("Laboratoire", "Action", 5){}; 

// destructeur 
Laboratoire::~Laboratoire(){}; 

// méthode d'affichage 
void Laboratoire::afficher() const{
    std::cout << "Laboratoire - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +2 cartes, +1 action" << std::endl;
}