#include <iostream> 
#include "Carte.hpp"
#include "Joueur.hpp"

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


// appliquer les effets de la carte sur le joueur, par défaut la carte ne fait rien 
void Carte::jouer(Joueur&){}; 

// applique les effets des cartes plus complexes 
void Carte::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){}; 