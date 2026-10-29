#ifndef BIBLIOTHEQUE_HPP
#define BIBLIOTHEQUE_HPP
#include "ActionPlateau.hpp"

class Bibliotheque : public ActionPlateau{

public: 
    Bibliotheque(); 
    ~Bibliotheque() override; 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&) override;
}; 


#endif