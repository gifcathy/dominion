#include <iostream>
#include "Bucheron.hpp"

// constructeur 
Bucheron::Bucheron() : Action("Bucheron", "Action", 3){}; 

// destructeur 
Bucheron::~Bucheron(){}; 

/*
void Bucheron::afficher() const {
    std::cout << "Bucheron, Cout : " << getCout() << std::endl;
}*/

// méthode d'affichage
void Bucheron::afficher() const{
    std::cout << "Bucheron - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 achat, +2 pièces" << std::endl;
}

// jouer la carte
void Bucheron::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : BUCHERON\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 achat et +2 pièces\n\n"; 
    joueur.ajouterAchats(1); 
    joueur.ajouterArgent(2); 
    std::cout << "Vous avez gagné un achat" << std::endl; 
    std::cout << "Vous avez gagné deux trésor" << std::endl; 
}