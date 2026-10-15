#ifndef CHAPELLE_HPP
#define CHAPELLE_HPP
#include "ActionActionAttaque.hpp"

class Joueur; 

class Chapelle : public ActionActionAttaque{

public : 
    Chapelle(); 
    ~Chapelle() override;
    
    void jouer(Joueur& joueur) override; 

}; 

#endif
