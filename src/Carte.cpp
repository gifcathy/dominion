#include <iostream> 
#include "Carte.hpp"

// constructeur 
Carte::Carte(const std::string& nom_carte, const std::string& type_carte, const int& cout_carte) : 
        nom(nom_carte), type(type_carte), cout(cout_carte){};
        
// destructeur 
Carte::~Carte(){}; 

// getter 
const std::string& Carte::getNom() const{
        return nom; 
}

const std::string& Carte::getType() const{
        return type; 
}

const int& Carte::getCout() const{
        return cout; 
}
