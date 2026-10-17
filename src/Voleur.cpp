#include <iostream> 
#include "Voleur.hpp"

// constructeur 
Voleur::Voleur() : ActionPlateau("Voleur", "Action-Attaque", 4){}; 

// destructeur 
Voleur::~Voleur(){}; 

// méthode d'affichage 
void Voleur::afficher() const{
    std::cout << "Voleur - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : Tous vos adversaires dévoilent les deux premières cartes de leur deck. S'ils dévoilent des cartes Trésor, ils en écartent une de votre choix. Parmi ces cartes Trésor écartées, recevez celles de votre choix. Les autres cartes dévoilées sont défaussées." 
              << std::endl;
}