#ifndef MINE_HPP
#define MINE_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Mine : public ActionPlateau{

public : 
    Mine(); 
    ~Mine(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif