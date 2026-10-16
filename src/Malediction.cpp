#include <iostream> 
#include "Malediction.hpp"

// constructeur
Malediction::Malediction() : Victoire("Malediction", -1, 0){}; 

// destructeur 
Malediction::~Malediction(){}; 

// méthode d'affichage 
void Malediction::afficher() const{
    std::cout << "Malédiction - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurVictoire() << "\n"
              << "Type de carte : Malédiction \n" 
              << "Description : -1 point de victoire" << std::endl;
}