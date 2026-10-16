#include <iostream>
#include "Sorciere.hpp"

// constructeur 
Sorciere::Sorciere() : ActionActionAttaque("Sorciere", "Action-Attaque", 5){}; 

// destructeur 
Sorciere::~Sorciere(){}; 

// méthode d'affichage 
void Sorciere::afficher() const{
    std::cout << "Sorcière - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +2 cartes, tous vos adversaires piochent une malédiction et la place sur leur défausse" 
              << std::endl;
}