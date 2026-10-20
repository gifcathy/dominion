#ifndef ATELIER_HPP
#define ATELIER_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Atelier : public ActionPlateau{

public : 
    Atelier(); 
    ~Atelier(); 

    void afficher() const override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 

}; 

#endif