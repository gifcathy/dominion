#ifndef FONDERIE_HPP
#define FONDERIE_HPP
#include "ActionPlateau.hpp"

class Fonderie : public ActionPlateau{

public : 
    Fonderie(); 
    ~Fonderie() override; 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;
};

#endif