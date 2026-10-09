#include "Plateau.hpp"

Plateau::Plateau(int nbJoueurs, const std::vector<std::string>& cartesAction){
    // Piles de Tresors
    piles["Cuivre"] = 60 - 7 * nbJoueurs;
    piles["Argent"] = 40;
    piles["Or"] = 30;

    // Piles de Victoire
    int nbVictoire = 0;

    if(nbJoueurs == 2){
        nbVictoire = 8;
    }
    else{
        nbVictoire = 12;
    }
    piles["Domaine"] = nbVictoire;
    piles["Duche"] = nbVictoire;
    piles["Province"] = nbVictoire;

    // Maledictions
    // 10 cartes Malédiction à 2 joueurs, 20 cartes Malédiction à 3 joueurs et 30 cartes Malédiction à 4 joueurs
    // Quantité adaptée au nombre de joueurs

    // Cartes Action choisies
    for (const auto& nom : cartesAction) {
        piles[nom] = 10;
    }
}