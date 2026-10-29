#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Espion.hpp"

#include "Joueur.hpp"
#include "Carte.hpp"

// constructeur 
Espion::Espion() : ActionPlateau("Espion", "Action-Attaque", 4){}; 

// destructeur 
Espion::~Espion(){}; 

// méthode d'affichage 
void Espion::afficher() const {
    std::cout << "Espion - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +1 carte, +1 action, Tous les joueur ainsi que vous dévoilent la 1er carte de leur deck. Vous décidez si chaque carte devoilée est déffaussée ou replacée sur son deck" 
              << std::endl;
}


// jouer la carte 
void Espion::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){

    std::cout << "\n========================================\n";
    std::cout << "            CARTE : ESPION\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 carte, +1 action, Tous les joueur ainsi que vous dévoilent la 1er "
              << "carte de leur deck. Vous décidez si chaque carte devoilée est déffaussée ou "
              << "replacée sur son deck \n\n"; 

    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    joueur.piocher();
    joueur.ajouterActions(1);

    std::cout << "\n--- Effet de l'Espion ---\n";

    // Chaque joueur révèle la première carte de son deck
    for (size_t i = 0; i < listeJoueurs.size(); ++i) {
        Joueur& joueurCible = listeJoueurs.at(i);

        // Si le deck est vide, on essaie de le reconstituer
        if (joueurCible.getCarteDessusDeck() == nullptr) {
            joueurCible.passerDefausseADeck();
        }

        const Carte* carte = joueurCible.getCarteDessusDeck();

        if (carte == nullptr) {
            std::cout << "Le joueur " << i + 1 << " n'a aucune carte a reveler.\n";
            continue;
        }

        std::cout << "\nLe joueur " << i + 1 << " revele : " << carte->getNom() << '\n';

        int choix = 0;

        do {
            std::cout << "1. Defausser la carte\n";
            std::cout << "2. Replacer la carte sur le deck\n";
            std::cout << "Votre choix : ";
            std::cin >> choix;
        } while (choix != 1 && choix != 2);

        if (choix == 1) {
            joueurCible.defausserCarteDessusDeck();
            std::cout << "La carte est defaussee.\n";
        } else {
            std::cout << "La carte reste sur le deck.\n";
        }
    }

}