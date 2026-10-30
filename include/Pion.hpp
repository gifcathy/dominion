#ifndef PION_HPP
#define PION_HPP
#include "Action.hpp"

class Pion : public Action{

public :
    Pion(); 
    ~Pion() override; 

    void afficher() const override; 
    void jouer(Joueur& joueur) override; 
}; 

#endif