#include <iostream>
#include "Forgeron.hpp"

// constructeur 
Forgeron::Forgeron() : Action("Forgeron", "Action", 4){}; 

// destructeur 
Forgeron::~Forgeron(){}; 

// méthode d'affichage 
void Forgeron::afficher() const{
    std::cout << "Forgeron - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +3 cartes" << std::endl;
}


// jouer la carte 
void Forgeron::jouer(Joueur& joueur){
    joueur.piocherPlusieurCarte(3);
    std::cout << "Vous venez de jouer la carte Forgeron" << std::endl;
}