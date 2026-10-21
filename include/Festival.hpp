#ifndef FESTIVAL_HPP
#define FESTIVAL_HPP
#include "Action.hpp"

class Festival : public Action {

public : 
    Festival(); 
    ~Festival() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif