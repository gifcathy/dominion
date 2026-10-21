#ifndef MARCHE_HPP
#define MARCHE_HPP
#include "Action.hpp"

class Marche : public Action{

public : 
    Marche(); 
    ~Marche() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif