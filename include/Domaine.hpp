#ifndef DOMAINE_HPP
#define DOMAINE_HPP
#include "Victoire.hpp"

class Domaine : public Victoire {

public : 
    Domaine(); 
    ~Domaine(); 

    void afficher() const override;
}; 

#endif