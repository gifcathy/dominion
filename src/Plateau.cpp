#include "Plateau.hpp"

#include "Carte.hpp"

Plateau::Plateau(int nbJoueurs, const std::vector<std::string>& cartesAction, const CatalogueCartes& catalogue) : catalogue(catalogue){
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
int Plateau::getNombreCartes(const std::string& nom) const{
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

bool Plateau::acheterCarte(const std::string& nom){
    std::map<std::string, int>::iterator it = piles.find(nom);

    if (it == piles.end() || it->second <= 0) {
        return false;
    }

    // decrémenter le nombre de carte dans la map
    --it->second;
    return true;
}


const std::map<std::string, int>& Plateau::getPiles() const{
    return piles;
}

void Plateau::afficher() const{
    for (const auto& element : piles)
    {
        std::cout << "\n----------------------\n";
        std::cout << "Cartes disponibles : " << element.first << std::endl;
        std::cout << "Cartes restantes : " << element.second << std::endl;

        std::unique_ptr<Carte> carte = catalogue.creer(element.first);
        carte->afficher();

        std::cout << "----------------------\n";
    }
}

void Plateau::afficherCartePourAchat() const{
    for (const auto& element : piles)
    {
        if (element.second > 0)
        {
            std::unique_ptr<Carte> carte = catalogue.creer(element.first);

            std::cout << carte->getNom() << " : "
                      << carte->getCout() << "p  |  ";
        }
    }

    std::cout << std::endl;
}

void Plateau::afficherCarteCoutInfEgal(int coutMax) const{
    for (const auto& element : piles)
    {
        // Vérifier qu'il reste des cartes dans la pile
        if (element.second > 0)
        {
            std::unique_ptr<Carte> carte = catalogue.creer(element.first);

            // Vérifier que le coût est inférieur ou égal au maximum
            if (carte->getCout() <= coutMax)
            {
                std::cout << carte->getNom() << " : " << carte->getCout() << "p | ";
            }
        }
    }
    std::cout << std::endl;
}

bool Plateau::contientCarte(const std::string& nom) const{
    std::map<std::string, int>::const_iterator it = piles.find(nom);

    if (it == piles.end()) {
        return false;
    }

    if (it->second <= 0) {
        return false;
    }

    return true;
}

int Plateau::getCoutCarte(const std::string& nom) const{
    std::unique_ptr<Carte> carte = catalogue.creer(nom);

    return carte->getCout();
}

// l'attribut catalogue est privé et donc on utilise cette méthode pour déléguer la création d'une carte
std::unique_ptr<Carte> Plateau::creerCarte(const std::string& nom) const {
    return catalogue.creer(nom);
}