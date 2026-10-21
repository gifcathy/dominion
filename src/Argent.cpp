#include <iostream> 
#include "Argent.hpp"

// constructeur 
Argent::Argent(): Tresor("Argent", 2, 3){}; 

// destructeur 
Argent::~Argent(){}; 

// méthode d'affichage 
void Argent::afficher() const {
    std::cout << "Argent - Cout : " << getCout() << "\n"
              << "Valeur : " << getValeurTresor() << "\n"
              << "Type de carte : Trésor \n" 
              << "Description : pièce ayant une valeur de 2"<<std::endl;
}