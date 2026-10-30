#include <iostream>
#include <limits>
#include "Chancelier.hpp"

// constructeur 
Chancelier::Chancelier() : Action("Chancelier", "Action", 3){}; 

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

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : CHANCELIER\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 pièces, vous pouvez immédiatement défausser votre deck\n\n"; 

    joueur.ajouterArgent(2);
    std::cout << "AVANT " << std::endl;
    std::cout << "Cartes dans le deck : " << joueur.getNbrCarteDeck() << std::endl;
    std::cout << "Cartes dans la defausse : " << joueur.getNbrCarteDefausse() << std::endl;
    std::cout << "Voulez vous défausser votre deck ? (y ou n) : ";
    char choix;
    std::cin >> choix;
    if(choix == 'y' || choix == 'Y'){
        joueur.defausseDeck();
    }
    std::cout << "APRES " << std::endl;
    std::cout << "Cartes dans le deck : " << joueur.getNbrCarteDeck() << std::endl;
    std::cout << "Cartes dans la defausse : " << joueur.getNbrCarteDefausse() << std::endl;
}