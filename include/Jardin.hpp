#ifndef JARDIN_HPP
#define JARDIN_HPP
#include "Victoire.hpp"

class Jardin : public Victoire{

public : 
    Jardin(); 
    ~Jardin(); 
    
    int getNbPointVictoireJardin(const int taille_deck) const; 
}; 

#endif 