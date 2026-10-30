#ifndef BARON_HPP
#define BARON_HPP
#include "ActionPlateau.hpp"

class Baron : public ActionPlateau{

public :
    Baron(); 
    ~Baron() override; 

    void afficher() const override; 
    void jouer(Joueur& joueur) override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;
}; 

#endif