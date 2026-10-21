#ifndef FORGERON_HPP
#define FORGERON_HPP
#include "Action.hpp"

class Forgeron : public Action {

public : 
    Forgeron(); 
    ~Forgeron() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif