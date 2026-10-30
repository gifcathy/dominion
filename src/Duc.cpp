#include <iostream>
#include <vector>
#include "Duc.hpp"

// constructeur 
Duc::Duc() : Victoire("Duc", 0, 5){}; 

// destructeur 
Duc::~Duc(){}; 

// méthode d'affichage 
void Duc::afficher() const{
    std::cout << "Duc - Cout : " << getCout() << "\n"
              << "Type de carte : Victoire \n" 
              << "Description : Vaut 1 point de victoire pour chaque Duché possédé" 
              << std::endl;
}

// getter 
// renvoie le nombre de duchés parce que 1 duché = 1 point de victoire
int Duc::getNbPointVictoireDuc(const Joueur& joueur) const{
    return joueur.getNombreCarte("Duche"); 
}

// pas de méthode pour jouer la carte parce qu'on compte les points en fin de partie dans joueur