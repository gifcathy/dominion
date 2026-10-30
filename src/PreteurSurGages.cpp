#include <iostream>
#include <limits>
#include "PreteurSurGages.hpp"

// constructeur 
PreteurSurGages::PreteurSurGages() : Action("PreteurSurGages", "Action", 4){}; 

// destructeur 
PreteurSurGages::~PreteurSurGages(){}; 


// méthode d'affichage 
void PreteurSurGages::afficher() const{
    std::cout << "PreteurSurGages - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez une carte Cuivre de votre main et recevez +3 pièces" << std::endl;
}

// jouer la carte 
void PreteurSurGages::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "       CARTE : PRETEUR SUR GAGES\n";
    std::cout << "========================================\n";
    std::cout << "Effet : écartez une carte Cuivre de votre main et recevez +3 pièces\n\n"; 

    const std::vector<std::unique_ptr<Carte>>& main = joueur.getMain();
    bool possedeCuivre = false;
    int idxCuivre = 0;

    for (std::size_t i = 0; i < main.size(); i++) {
        if (main[i]->getNom() == "Cuivre") {
            possedeCuivre = true;
            idxCuivre = i;
            break;
        }
    }

    if(possedeCuivre){
        joueur.ecarterCarte(idxCuivre);
        joueur.ajouterArgent(3);
        std::cout << "Vous venez de jouer la carte Prêteur sur gages" << std::endl;
        std::cout << "Un Cuivre de votre main viens d'être écarté" << std::endl;
        std::cout << "Vous avez reçu +3 pièces" << std::endl;
    }
    else{
        std::cout << "Vous n'aviez pas de Cuivre, donc rien ne s'est passé" << std::endl;
    }
}