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

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : LABORATOIRE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 cartes, +1 action\n\n"; 

    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(2); 
    std::cout << "Vous avez pioché : " << std::endl; 
    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    }
    joueur.ajouterActions(1); 
    std::cout << "Vous venez de jouer la carte Laboratoire" << std::endl;
}