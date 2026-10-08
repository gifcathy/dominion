#ifndef VICTOIRE_HPP
#define VICTOIRE_HPP
#include "Carte.hpp"

class Victoire : public Carte {

private : 
    int valeur; 

public : 
    Victoire(const std::string& nom_carte, const int& valeur_carte, const int& cout_carte); 
    ~Victoire(); 

}; 

#endif 