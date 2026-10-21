#include <iostream>
#include "Domaine.hpp"

// constructeur 
Domaine::Domaine(): Victoire("Domaine", 1, 2){}; 

// destructeur 
Domaine::~Domaine(){}; 

// méthode d'affichage
void Domaine::afficher() const {
    std::cout << "Domaine - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurVictoire() << "\n"
              << "Type de carte : Victoire \n"
              << "Descirption : carte offrant 1 point de victoire" << std::endl;
}