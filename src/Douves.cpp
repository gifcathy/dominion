#include <iostream>
#include "Douves.hpp"

// constructeur 
Douves::Douves() : ActionReaction("Douves", "Action-Réaction", 2){}; 

// destructeur 
Douves::~Douves(){}; 

// méthode d'affichage 
void Douves::afficher() const{
    std::cout << "Douves - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Réaction \n" 
              << "Description : +2 Cartes, lorsqu'un adversaire joue une carte Attaque, vous pouvez dévoiler cette carte de votre main. Dans ce cas l'attaque n'a pas d'effet sur vous" 
              << std::endl;
}

// jouer la carte 
void Douves::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "            CARTE : DOUVES\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 Cartes, lorsqu'un adversaire joue une carte Attaque, vous pouvez "
              << "dévoiler cette carte de votre main. Dans ce cas l'attaque n'a pas d'effet sur vous\n\n";

    joueur.piocherPlusieurCarte(2); 
    std::cout << "Vous venez de jouer la carte Douves" << std::endl;
}