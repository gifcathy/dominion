#ifndef CHAPELLE_HPP
#define CHAPELLE_HPP
#include "Action.hpp"

class Joueur; 

class Chapelle : public Action{

public : 
    Chapelle(); 
    ~Chapelle() override;
    
    void afficher() const override;
    void jouer(Joueur& joueur) override; 

}; 

#endif
