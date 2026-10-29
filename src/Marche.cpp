#include <iostream>
#include "Marche.hpp"

// constructeur 
Marche::Marche() : Action("Marche", "Action", 5){}; 

// destructeur 
Marche::~Marche(){}; 

// méthode d'affichage 
void Marche::afficher() const{
    std::cout << "Marche - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 carte, +1 Action, +1 achat, +1 pièce" << std::endl;
}


// jouer la carte 
void Marche::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : MARCHE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 carte, +1 Action, +1 achat, +1 pièce\n\n"; 

    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(1); 
    std::cout << "Vous avez pioché : " << std::endl; 
    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    }
    joueur.ajouterActions(1);
    joueur.ajouterAchats(1);
    joueur.ajouterArgent(1);
    std::cout << "Vous venez de jouer la carte Marche" << std::endl;
}