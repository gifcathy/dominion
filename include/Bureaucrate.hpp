#ifndef BUREAUCRATE_HPP
#define BUREAUCRATE_HPP
#include "ActionPlateau.hpp"

class Joueur;
class Plateau;

class Bureaucrate : public ActionPlateau {

public : 
    Bureaucrate(); 
    ~Bureaucrate(); 

    void afficher() const override; 
    void jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) override; 
}; 

#endif