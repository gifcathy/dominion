#ifndef COMPTOIR_HPP
#define COMPTOIR_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Comptoir : public ActionPlateau {

public : 
    Comptoir(); 
    ~Comptoir() override;

    void afficher() const override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif