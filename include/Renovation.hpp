#ifndef RENOVATION_HPP
#define RENOVATION_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Renovation : public ActionPlateau{

public : 
    Renovation(); 
    ~Renovation(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif