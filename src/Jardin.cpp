#include <iostream>
#include "Jardin.hpp"
#include <cmath>

// constructeur 
Jardin::Jardin() : Victoire("Jardin", 0, 4){}; 

// destructeur 
Jardin::~Jardin(){}; 

// getter 
const int Jardin::getNbPointVictoireJardin(const int taille_deck) const{
    return std::floor(taille_deck/10); 
}