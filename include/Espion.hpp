#ifndef ESPION_HPP
#define ESPION_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Espion : public ActionPlateau {

public : 
    Espion(); 
    ~Espion(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override; 
}; 

#endif