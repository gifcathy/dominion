#include <iostream>
#include "Festival.hpp"

// constructeur 
Festival::Festival() : Action("Festival", "Action", 5){}; 

// destructeur 
Festival::~Festival(){}; 

// méthode d'affichage 
void Festival::afficher() const{
    std::cout << "Festival - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +2 actions, +1 achat, +2 pièces" << std::endl;
}


// jouer la carte 
void Festival::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "            CARTE : FESTIVAL\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 actions, +1 achat, +2 pièces\n\n"; 

    joueur.ajouterActions(2); 
    joueur.ajouterAchats(1); 
    joueur.ajouterArgent(2);
    std::cout << "Vous venez de jouer la carte Festival" << std::endl;
}