#include <iostream>
#include "Bucheron.hpp"

// constructeur 
Bucheron::Bucheron() : ActionActionAttaque("Bucheron", "Action", 3){}; 

// destructeur 
Bucheron::~Bucheron(){}; 

void Bucheron::afficher() const {
    std::cout << "Bucheron, Cout : "
              << getCout()
              << std::endl;
}