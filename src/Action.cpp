#include <iostream> 
#include "Action.hpp"

// constructeur 
Action::Action(const std::string& nom_carte, const std::string& type_carte, 
        const int& cout_carte) : Carte(nom_carte, type_carte, cout_carte){}; 

// destructeur
Action::~Action(){}; 