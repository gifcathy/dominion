#include <iostream> 
#include "Atelier.hpp"

// constructeur
Atelier::Atelier() : ActionActionAttaque("Atelier", "Action", 3){}; 

// destructeur 
Atelier::~Atelier(){}; 

// méthode d'affichage
void Atelier::afficher() const {
    std::cout << "Atelier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Recevez une carte coûtant jusqu'à 4 pièces" << std::endl;
}