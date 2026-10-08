#include <iostream> 
#include "Victoire.hpp"

// constructeur 
Victoire::Victoire(const std::string& nom_carte, const int& valeur_carte, const int& cout_carte) :
    Carte(nom_carte, valeur_carte, "Victoire", cout_carte){}; 

// destructeur 
Victoire::~Victoire(){}; 