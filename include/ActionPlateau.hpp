#ifndef ACTIONPLATEAU_HPP
#define ACTIONPLATEAU_HPP
#include "Carte.hpp"

#include <vector>

class Joueur; 
class Plateau; 

class ActionPlateau : public Carte{

public : 
    ActionPlateau(const std::string& nom_carte, const std::string& type_carte, 
        const int& cout_carte); 
    //virtual ~ActionPlateau(); 
    virtual void jouerPlateau(std::vector<Joueur>& joueurs, int joueurActuel, Plateau& plateau) = 0;

    virtual void jouerPlateau(std::vector<Joueur>& listeJoueurs,int& indiceJoueurActuel,
        Plateau& plateau) override;
}; 

#endif