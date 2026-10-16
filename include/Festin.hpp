#ifndef FESTIN_HPP
#define FESTIN_HPP
#include "ActionActionAttaque.hpp"

class Festin : public ActionActionAttaque{

public : 
    Festin(); 
    ~Festin(); 

    void afficher() const override; 
}; 

#endif