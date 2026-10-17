#ifndef LABORATOIRE_HPP
#define LABORATOIRE_HPP
#include "Action.hpp"
#include "Joueur.hpp"

class Laboratoire : public Action {

public :
    Laboratoire(); 
    ~Laboratoire(); 

    void afficher() const override; 
    void jouer(Joueur& joueur) override;
}; 

#endif 