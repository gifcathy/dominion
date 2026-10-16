#ifndef VOLEUR_HPP
#define VOLEUR_HPP
#include "ActionActionAttaque.hpp"

class Voleur : public ActionActionAttaque {

public : 
    Voleur(); 
    ~Voleur(); 

    void afficher() const override; 
}; 

#endif 