#ifndef CHANCELIER_HPP
#define CHANCELIER_HPP
#include "Action.hpp"

class Joueur; 

class Chancelier : public Action {

public : 
    Chancelier(); 
    ~Chancelier() override;
    
    void afficher() const override;
    void jouer(Joueur& joueur) override; 

}; 

#endif
