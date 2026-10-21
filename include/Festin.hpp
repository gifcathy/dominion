#ifndef FESTIN_HPP
#define FESTIN_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Festin : public ActionPlateau{

public : 
    Festin(); 
    ~Festin(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif