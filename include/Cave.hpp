#ifndef CAVE_HPP
#define CAVE_HPP
#include "Action.hpp"

class Joueur; 

class Cave : public Action {

public : 
    Cave(); 
    ~Cave() override;
    
    void afficher() const override;
    void jouer(Joueur& joueur) override; 

}; 

#endif
