#ifndef PARTIE_HPP
#define PARTIE_HPP
#include "Plateau.hpp"
#include "Joueur.hpp"
#include "CatalogueCartes.hpp"

#include <memory>
#include <vector>

class Partie {
private:
    CatalogueCartes catalogue;
    Plateau plateau;
    std::vector<Joueur> joueurs;
    int joueurActuel;

    std::vector<std::unique_ptr<Carte>> creerDeckInitial();

public:
    Partie(int nombreJoueurs, const std::vector<std::string>& cartesAction);

    void commencer();
    void tour();
    void acheterCarte();
    void finTour();

    bool estTerminee() const;
};

#endif 