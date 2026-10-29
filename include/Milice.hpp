#ifndef MILICE_HPP
#define MILICE_HPP
#include "ActionPlateau.hpp"

class Milice : public ActionPlateau{

public:
    Milice(); 
    ~Milice() override; 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;

}; 

#endif