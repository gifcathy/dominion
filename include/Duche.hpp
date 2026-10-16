#ifndef DUCHE_HPP
#define DUCHE_HPP
#include "Victoire.hpp"

class Duche : public Victoire{

public : 
    Duche(); 
    ~Duche(); 

    void afficher() const override;
}; 

#endif 