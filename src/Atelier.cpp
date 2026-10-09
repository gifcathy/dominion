#include <iostream> 
#include "Atelier.hpp"

// constructeur
Atelier::Atelier() : ActionActionAttaque("Atelier", "Action", 3){}; 

// destructeur 
Atelier::~Atelier(){}; 

void Atelier::afficher() const {
    std::cout << "Atelier, Cout : "
              << getCout()
              << std::endl;
}