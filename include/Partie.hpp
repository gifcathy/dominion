#ifndef PARTIE_HPP
#define PARTIE_HPP
#include "Plateau.hpp"
#include "Joueur.hpp"


class Partie {
private:
    Plateau plateau;
    std::vector<Joueur> joueurs;
    int joueurActuel;

public:
    Partie(int nombreJoueurs);

    void commencer();
    void tour();
    void acheterCarte();
    void finTour();

    bool estTerminee() const;
};

#endif 