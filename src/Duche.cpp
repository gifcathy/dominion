#include <iostream> 
#include "Duche.hpp"

// constructeur 
Duche::Duche() : Victoire("Duché", 3, 5){}; 

// destructeur 
Duche::~Duche(){}; 

void Duche::afficher() const {
    std::cout << "Duché - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurVictoire() << "\n"
              << "Type de carte : Victoire \n"
              << "Descirption : carte offrant 3 point de victoire" << std::endl;
}