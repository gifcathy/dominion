#ifndef BUCHERON_HPP
#define BUCHERON_HPP
#include "Action.hpp"

class Bucheron : public Action{

public : 
    Bucheron(); 
    ~Bucheron() override; // les destructeur héritent du destructeur virtuel de carte et donc saura dans 
    // quel ordre il faudra les appeler 

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif