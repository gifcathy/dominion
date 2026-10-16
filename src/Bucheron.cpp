#include <iostream>
#include "Bucheron.hpp"

// constructeur 
Bucheron::Bucheron() : ActionActionAttaque("Bucheron", "Action", 3){}; 

// destructeur 
Bucheron::~Bucheron(){}; 

void Bucheron::afficher() const {
    std::cout << "Bucheron, Cout : " << getCout() << std::endl;
}

// méthode d'affichage
void Bucheron::afficher() const{
    std::cout << "Bucheron - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 achat, +2 pièces" << std::endl;
}

// jouer la carte
void Bucheron::jouer(Joueur& joueur){
    joueur.ajouterAchats(1); 
    joueur.ajouterArgent(2); 
}