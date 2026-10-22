#include <iostream>
#include <limits>
#include "Chancelier.hpp"

// constructeur 
Chancelier::Chancelier() : Action("Chancelier", "Action", 2){}; 

// destructeur 
Chancelier::~Chancelier(){}; 


// méthode d'affichage 
void Chancelier::afficher() const{
    std::cout << "Chancelier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +2 pièces, vous pouvez immédiatement défausser votre deck" << std::endl;
}

// jouer la carte 

void Chancelier::jouer(Joueur& joueur) {
    joueur.ajouterArgent(2);
    std::cout << "Voulez vous défausser votre deck ? (y ou n) : ";
    char choix;
    std::cin >> choix;
    if(choix == 'y' || choix == 'Y'){
        joueur.defausseDeck();
    }
}