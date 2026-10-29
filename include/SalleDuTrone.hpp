#ifndef SALLE_DU_TRONE_HPP
#define SALLE_DU_TRONE_HPP
#include "Action.hpp"

class SalleDuTrone : public Action {

public : 
    SalleDuTrone(); 
    ~SalleDuTrone() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif