#include <iostream> 
#include "Argent.hpp"

// constructeur 
Argent::Argent(): Tresor("Argent", 2, 3){}; 

// destructeur 
Argent::~Argent(){}; 

void Argent::afficher() const {
    std::cout << "Argent - Valeur : "
              << getValeurTresor()
              << ", Cout : "
              << getCout()
              << std::endl;
}