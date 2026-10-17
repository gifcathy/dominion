#ifndef SORCIERE_HPP
#define SORCIERE_HPP
#include "ActionPlateau.hpp"

class Sorciere : public ActionPlateau {

public : 
    Sorciere(); 
    ~Sorciere(); 

    void afficher() const override; 
    
    void jouer(Joueur& joueur) override;

    void jouerPlateau(std::vector<Joueur>& joueurs, int joueurActuel, Plateau& plateau) override;
}; 

#endif 