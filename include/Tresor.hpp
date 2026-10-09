#ifndef TRESOR_HPP
#define TRESOR_HPP 
#include "Carte.hpp"

class Tresor : public Carte {

private : 
    int valeur; 

public : 
    Tresor(const std::string& nom_carte, const int& valeur_carte, const int& cout_carte); 
    virtual ~Tresor(); 

    const int& getValeurTresor() const; 

}; 

#endif