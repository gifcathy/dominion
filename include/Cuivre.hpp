#ifndef CUIVRE_HPP
#define CUIVRE_HPP 
#include "Tresor.hpp"

class Cuivre : public Tresor {

public : 
    Cuivre(); 
    ~Cuivre() override; 

    void afficher() const override;

}; 


#endif 