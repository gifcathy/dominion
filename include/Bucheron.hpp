#ifndef BUCHERON_HPP
#define BUCHERON_HPP
#include "ActionActionAttaque.hpp"

class Bucheron : public ActionActionAttaque{

public : 
    Bucheron(); 
    ~Bucheron() override; // les destructeur héritent du destructeur virtuel de carte et donc saura dans 
    // quel ordre il faudra les appeler 

    void afficher() const override;
    void jouer(Joueur& joueur) override;
}; 

#endif