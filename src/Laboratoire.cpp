#include <iostream>
#include "Laboratoire.hpp"

// constructeur 
Laboratoire::Laboratoire() : Action("Laboratoire", "Action", 5){}; 

// destructeur 
Laboratoire::~Laboratoire(){}; 

// méthode d'affichage 
void Laboratoire::afficher() const{
    std::cout << "Laboratoire - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +2 cartes, +1 action" << std::endl;
}


// jouer la carte 
void Laboratoire::jouer(Joueur& joueur){
    joueur.piocherPlusieurCarte(2); 
    joueur.ajouterActions(1); 
    std::cout << "Vous venez de jouer la carte Laboratoire" << std::endl;
}