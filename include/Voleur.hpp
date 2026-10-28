#ifndef VOLEUR_HPP
#define VOLEUR_HPP
#include "ActionPlateau.hpp"

class Voleur : public ActionPlateau {

public : 
    Voleur(); 
    ~Voleur(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;
}; 

#endif 