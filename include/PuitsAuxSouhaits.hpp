#ifndef PUITSAUXSOUHAITS_HPP
#define PUITSAUXSOUHAITS_HPP
#include "ActionPlateau.hpp"

class PuitsAuxSouhaits : public ActionPlateau{

public :
    PuitsAuxSouhaits();
    ~PuitsAuxSouhaits() override; 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;

}; 

#endif