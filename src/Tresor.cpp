#include <iostream>
#include "Tresor.hpp"

// constructeur 
Tresor::Tresor(const std::string& nom_carte, const int& valeur_carte, const int& cout_carte) :
    Carte(nom_carte, "Trésor", cout_carte), valeur(valeur_carte){}; 

// destructeur 
Tresor::~Tresor(){}; 

// getter
const int& Tresor::getValeurTresor() const{
    return valeur; 
}

// jouer un trésor 
void Tresor::jouer(Joueur& joueur){
    joueur.ajouterArgent(valeur); 
}