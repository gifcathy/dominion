#ifndef PRETEUR_SUR_GAGES_HPP
#define PRETEUR_SUR_GAGES_HPP
#include "Action.hpp"

class PreteurSurGages : public Action {

public : 
    PreteurSurGages(); 
    ~PreteurSurGages() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif