#ifndef AVENTURIER_HPP
#define AVENTURIER_HPP
#include "ActionPlateau.hpp"

class Aventurier : public ActionPlateau {

public : 
    Aventurier(); 
    ~Aventurier() override; 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;
}; 

#endif