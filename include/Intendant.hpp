#ifndef INTENDANT_HPP
#define INTENDANT_HPP
#include "Action.hpp"

class Intendant : public Action {

public :
    Intendant(); 
    ~Intendant(); 

    void afficher() const override; 
    void jouer(Joueur& joueur) override;
}; 

#endif 