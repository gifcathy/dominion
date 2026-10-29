#include <iostream>
#include <limits>
#include "SalleDuTrone.hpp"

// constructeur 
SalleDuTrone::SalleDuTrone() : Action("SalleDuTrone", "Action", 4){}; 

// destructeur 
SalleDuTrone::~SalleDuTrone(){}; 


// méthode d'affichage 
void SalleDuTrone::afficher() const{
    std::cout << "SalleDuTrone - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Choisissez 1 carte Action de votre main. Jouez-la deux fois" << std::endl;
}

// jouer la carte 
void SalleDuTrone::jouer(Joueur& joueur){
    std::vector<std::size_t> indicesActions;

    std::cout << "\n========================================\n";
    std::cout << "       CARTE : SALLE DU TRONE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Choisissez 1 carte Action de votre main. Jouez-la deux fois\n\n"; 

    // Afficher uniquement les cartes Action
    for (std::size_t i = 0; i < joueur.getMain().size(); ++i) {

        if (joueur.getCarte(i) != nullptr && joueur.getCarte(i)->getType() != "Tresor" && joueur.getCarte(i)->getType() != "Victoire") {

            indicesActions.push_back(i);

            std::cout << indicesActions.size() << ". " << joueur.getCarte(i)->getNom() << '\n';
        }
    }

    // Aucune carte Action disponible
    if (indicesActions.empty()) {
        std::cout << "Aucune carte Action en main.\n";
        return;
    }

    // Demander le choix du joueur
    std::size_t choix = 0;

    do {
        std::cout << "Votre choix : ";
        std::cin >> choix;
    } while (choix == 0 || choix > indicesActions.size());

    // Jouer la carte choisie deux fois
    joueur.jouerActionDeuxFois(indicesActions[choix - 1]);
}