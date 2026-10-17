#ifndef FESTIN_HPP
#define FESTIN_HPP
#include "ActionPlateau.hpp"

class Festin : public ActionPlateau{

public : 
    Festin(); 
    ~Festin(); 

    void afficher() const override; 
}; 

#endif