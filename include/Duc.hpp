#ifndef DUC_HPP
#define DUC_HPP
#include "Victoire.hpp"

class Joueur; 

class Duc : public Victoire{

public : 
    Duc(); 
    ~Duc() override; 
    
    int getNbPointVictoireDuc(const Joueur& joueur) const; 
    void afficher() const override; 
}; 

#endif