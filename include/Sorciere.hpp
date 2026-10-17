#ifndef SORCIERE_HPP
#define SORCIERE_HPP
#include "ActionPlateau.hpp"

class Sorciere : public ActionPlateau {

public : 
    Sorciere(); 
    ~Sorciere(); 

    void afficher() const override; 
}; 

#endif 