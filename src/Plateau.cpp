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
        if(nom == "Jardin" && nbJoueurs == 2){
            piles[nom] = 8;
        }
        else if (nom == "Jardin" && nbJoueurs > 2)
        {
            piles[nom] = 12;
        }
        else
        {
            piles[nom] = 10;
        }
    }
}


//ATTENTION A REVOIR les deux fonction
int Plateau::getNombreCartes(const std::string& nom) const
{
    // La méthode find() recherche une clé dans la map -> renvoie un itérateur
    // const_iterator est un itérateur qui permet de lire un élément, mais pas de modifier sa valeur
    std::map<std::string, int>::const_iterator it = piles.find(nom);

    //end() n'est la dernière carte, c une position spéciale située après tous les éléments de la collection
    if (it == piles.end()) {
        return 0;
    }

    // map contient deux éléments :
    // - first : la clé, (nom)
    // - second : la valeur, (nombre)
    return it->second;
}

bool Plateau::acheterCarte(const std::string& nom)
{
    std::map<std::string, int>::iterator it = piles.find(nom);

    if (it == piles.end() || it->second <= 0) {
        return false;
    }

    // decrémenter le nombre de carte dans la map
    --it->second;
    return true;
}
