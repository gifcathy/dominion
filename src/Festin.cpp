#include <iostream>
#include "Festin.hpp"

// constructeur 
Festin::Festin() : ActionActionAttaque("Festin", "Action", 4){}; 

// destructeur 
Festin::~Festin(){}; 

// méthode d'affichage 
void Festin::afficher() const{
    std::cout << "Festin - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez cette carte, recevez une carte coûtant jusqu'à 5 pièces" 
              << std::endl;
}