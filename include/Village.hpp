#ifndef VILLAGE_HPP
#define VILLAGE_HPP
#include "Action.hpp"

class Village : public Action{

public :
    Village(); 
    ~Village(); 

    void afficher() const override; 
    void jouer(Joueur& joueur) override;
}; 

#endif 