#ifndef VOLEUR_HPP
#define VOLEUR_HPP
#include "ActionPlateau.hpp"

class Voleur : public ActionPlateau {

public : 
    Voleur(); 
    ~Voleur(); 

    void afficher() const override; 
}; 

#endif 