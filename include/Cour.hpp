#ifndef COUR_HPP
#define COUR_HPP
#include "Action.hpp"

class Joueur; 

class Cour : public Action {

public : 
    Cour(); 
    ~Cour() override;
    
    void afficher() const override;
    void jouer(Joueur& joueur) override; 
}; 

#endif
