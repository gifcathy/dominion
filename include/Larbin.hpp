#ifndef LARBIN_HPP
#define LARBIN_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Larbin : public ActionPlateau {

public : 
    Larbin(); 
    ~Larbin() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override; 
}; 

#endif