#include <iostream>
#include "Village.hpp"

// constructeur 
Village::Village() : Action("Village", "Action", 3){}; 

// destructeur 
Village::~Village(){}; 

// méthode d'affichage 
void Village::afficher() const{
    std::cout << "Village - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 carte, + 2 actions" << std::endl;
}


// jouer la carte 
void Village::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : VILLAGE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 carte, + 2 actions\n\n"; 

    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(1); 
    std::cout << "Vous avez pioché : " << std::endl; 
    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    } 
    joueur.ajouterActions(2); 
}