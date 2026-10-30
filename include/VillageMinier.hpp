#ifndef VILLAGE_MINIER_HPP
#define VILLAGE_MINIER_HPP
#include "Action.hpp"

class VillageMinier : public Action {

public :
    VillageMinier(); 
    ~VillageMinier(); 

    void afficher() const override; 
    void jouer(Joueur& joueur) override;
}; 

#endif 