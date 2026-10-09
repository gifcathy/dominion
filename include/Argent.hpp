#ifndef ARGENT_HPP
#define ARGENT_HPP 
#include "Tresor.hpp"

class Argent : public Tresor {

public : 
    Argent(); 
    ~Argent(); 

    void afficher() const override;

}; 

#endif 