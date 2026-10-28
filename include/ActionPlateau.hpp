#ifndef ACTIONPLATEAU_HPP
#define ACTIONPLATEAU_HPP
#include "Carte.hpp"

#include <vector>

class Joueur; 
class Plateau; 

class ActionPlateau : public Carte{

public :

    ActionPlateau(const std::string& nom_carte, const std::string& type_carte, const int& cout_carte);

    virtual void jouerPlateau(std::vector<Joueur>& joueurs, int& joueurActuel, Plateau& plateau) override = 0;

}; 

#endif