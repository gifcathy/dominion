#include <iostream>
#include "Province.hpp"

// constructeur 
Province::Province() : Victoire("Province", 6, 8){}; 

// destructeur 
Province::~Province(){}; 

// méthode d'affichage
void Province::afficher() const {
    std::cout << "Province - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurVictoire() << "\n"
              << "Type de carte : Victoire \n"
              << "Descirption : carte offrant 6 point de victoire" << std::endl;
}