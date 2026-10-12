#include <iostream>
#include "Domaine.hpp"

// constructeur 
Domaine::Domaine(): Victoire("Domaine", 1, 2){}; 

// destructeur 
Domaine::~Domaine(){}; 

void Domaine::afficher() const {
    std::cout << "Domaine - Cout : "
              << getCout()
              << std::endl;
}