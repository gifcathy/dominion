#ifndef MISE_A_NIVEAU_HPP
#define MISE_A_NIVEAU_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class MiseANiveau : public ActionPlateau {

public : 
    MiseANiveau(); 
    ~MiseANiveau() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif