#ifndef MALEDICTION_HPP
#define MALEDICTION_HPP
#include "Victoire.hpp"

class Malediction : public Victoire{

public : 
    Malediction(); 
    ~Malediction(); 

    void afficher() const override; 
}; 

#endif