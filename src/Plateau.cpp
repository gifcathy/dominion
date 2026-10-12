#include "Plateau.hpp"

Plateau::Plateau(int nbJoueurs, const std::vector<std::string>& cartesAction){
    // Piles de Tresors
    piles["Cuivre"] = 60 - 7 * nbJoueurs;
    piles["Argent"] = 40;
    piles["Or"] = 30;

    // Piles de Victoire et Maledictions
    int nbVictoire = 0;
    int nbMalediction = 0;

    if(nbJoueurs == 2){
        nbVictoire = 8;
        nbMalediction = 10;
    }
    else if (nbJoueurs == 3){
        nbVictoire = 12;
        nbMalediction = 20;
    }
    else{
        nbVictoire = 12;
        nbMalediction = 30;
    }
    piles["Domaine"] = nbVictoire;
    piles["Duche"] = nbVictoire;
    piles["Province"] = nbVictoire;
    piles["Malediction"] = nbMalediction;


    // Cartes Action choisies
    for (const auto& nom : cartesAction) {
        piles[nom] = 10;
    }
}


//ATTENTION A REVOIR les deux fonction
int Plateau::getNombreCartes(const std::string& nom) const
{
    std::map<std::string, int>::const_iterator it = piles.find(nom);

    if (it == piles.end()) {
        return 0;
    }

    return it->second;
}
bool Plateau::acheterCarte(const std::string& nom)
{
    std::map<std::string, int>::iterator it = piles.find(nom);

    if (it == piles.end() || it->second <= 0) {
        return false;
    }

    --it->second;
    return true;
}
