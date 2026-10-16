#ifndef SORCIERE_HPP
#define SORCIERE_HPP
#include "ActionActionAttaque.hpp"

class Sorciere : public ActionActionAttaque {

public : 
    Sorciere(); 
    ~Sorciere(); 

    void afficher() const override; 
}; 

#endif 