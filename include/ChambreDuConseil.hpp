#ifndef CHAMBRE_DU_CONSEIL_HPP
#define CHAMBRE_DU_CONSEIL_HPP
#include "ActionPlateau.hpp"

class ChambreDuConseil : public ActionPlateau {

public : 
    ChambreDuConseil(); 
    ~ChambreDuConseil() override;

    void afficher() const override;
    void jouer(Joueur& joueur) override;
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override; 
}; 

#endif