#include <iostream> 
#include "ActionActionAttaque.hpp"

// constructeur 
ActionActionAttaque::ActionActionAttaque(const std::string& nom_carte, const std::string& type_carte, 
        const int& cout_carte) : Carte(nom_carte, type_carte, cout_carte){}; 

// destructeur
ActionActionAttaque::~ActionActionAttaque(){}; 